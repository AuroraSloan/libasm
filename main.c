#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define STAR "****************"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define RESET "\033[0m"
#define BUF_SIZE 3

extern size_t ft_strlen(const char *s);
extern char *ft_strcpy(char *dst, const char*src);
extern int ft_strcmp(const char *s1, const char *s2);
extern ssize_t ft_write(int fd, const void *buff, size_t size);
extern ssize_t ft_read(int fd, const void *buff, size_t count);
extern char *ft_strdup(const char *s);

/**************FT_STRLEN*****************/
void compare_len(const char *s)
{
	size_t len = strlen(s);
	size_t ft_len = ft_strlen(s);
	if (len != ft_len)
	{
		printf("%sFAIL%s\n", RED, RESET);
		return;
	}
	printf("%sPASS%s\n", GREEN, RESET);
}

void test_strlen(const char *long_string)
{
	printf("%sFT_STRLEN%s\n", STAR, STAR);

	compare_len("Hello, this is a string");
	compare_len("a");
	compare_len("");
	compare_len(long_string);
	compare_len("Hello, this string has a new line\n and a \ttab");
	compare_len("escaping this\0string");
}

/**************FT_STRCPY*****************/
void compare_cpy(const char *src)
{
	// allocate dst
	char *dst = (char *)malloc(strlen(src) + 1);
	if (dst == NULL)
	{
		fprintf(stderr, "%smalloc failed%s\n", RED, RESET);
		return;
	}

	// run clib strcpy and check result of dst
	char *ret = strcpy(dst, src);
	int cmp = strcmp(dst, src);

	// erase dst and run ft function and check restul of dst
	memset(dst, '\0', strlen(dst));
	char *ft_ret = ft_strcpy(dst, src);
	int ft_cmp = strcmp(dst, src);

	// compare return and result of clib with ft
	if (cmp == ft_cmp && ret == ft_ret)
	{
		printf("%sPASS%s\n", GREEN, RESET);
	}
	else
	{
		printf("%sFAIL%s\n", RED, RESET);
	}
	free(dst);
}

void test_strcpy(const char *long_string)
{
	printf("\n%sFT_STRCPY%s\n", STAR, STAR);	

	compare_cpy("Hello, this is a string");
	compare_cpy("a");
	compare_cpy("");
	compare_cpy(long_string);
	compare_cpy("Hello, this string has a new line\n and a \ttab");
	compare_cpy("escaping this\0string");
}

/**************FT_STRCMP*****************/
void compare_cmp(const char *s1, const char *s2)
{
	int ret = strcmp(s1, s2);
	int ft_ret = ft_strcmp(s1, s2);

	if (ret != ft_ret)
	{
		printf("%sFAIL%s\n", RED, RESET);
		return;
	}
	printf("%sPASS%s\n", GREEN, RESET);
}

void test_strcmp(char *ls1, char *ls2)
{
	printf("\n%sFT_STRCMP%s\n", STAR, STAR);

	compare_cmp("", "");
	compare_cmp("aaa", "aaa");
	compare_cmp("aaa", "AAA");
	compare_cmp("AAA", "aaa");
	compare_cmp("baa", "aaa");
	compare_cmp("aaa", "aba");
	compare_cmp("aaaa", "aaa");
	compare_cmp("aaa", "aaaa");
	compare_cmp("aaa", "qaa");
	compare_cmp("aaa\t", "aaa");
	compare_cmp("aaa", "aaa\t");
	compare_cmp(ls1, ls2);
	ls1[1000] = 'z';
	compare_cmp(ls1, ls2);
	ls1[1000] = '.';
	ls2[1001] = 'z';
	compare_cmp(ls1, ls2);
	ls2[1001] = '.';
	ls1[1040] = '\0';
	compare_cmp(ls1, ls2);
	ls1[1040] = '.';
	ls2[1039] = '\0';
}

/**************FT_WRITE*****************/
void test_write()
{
	printf("\n%sFT_WRITE%s\n", STAR, STAR);
	int fd = 2;
	char *str = "write this string\n";
	size_t write_len = strlen(str);

	write(2, "write:    ", 10);
	ssize_t bytes = write(fd, str, write_len);
	int write_errno = errno;

	write(2, "ft_write: ", 10);
	ssize_t ft_bytes = ft_write(fd, str, write_len);
	int ft_write_errno = errno;
	printf("%d\n", errno);

	printf("\n      |  clib   |   ft  |\n");
	printf("      |=================|\n");
	printf("bytes |   %zd     |   %zd   |\n", bytes, ft_bytes);
	printf("errno |   %d     |   %d   |\n", write_errno, ft_write_errno);
}

/**************FT_READ*****************/
void test_read()
{
	printf("\n%sFT_READ%s\n", STAR, STAR);
	int read_errno = 0;
	int ft_read_errno = 0;
	char buffer[BUF_SIZE];
	int bytes_read;
	char *read_file_name = "read_file";
	char *read_content = "hello, this is in the read file\n";
	int read_fd = open(read_file_name, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	if (read_fd == -1)
	{
		printf("could not open read_fd");
	}
	int written_bytes = write(read_fd, read_content, strlen(read_content));
	if (written_bytes == -1)
	{
		printf("could not open write to read_fd");
	}
	close(read_fd);
	read_fd = open(read_file_name, O_RDONLY);	
	if (read_fd == -1)
	{
		printf("could not open read_fd for reading");
	}
	printf("read:    ");
	while ((bytes_read = read(read_fd, buffer, BUF_SIZE - 1)) > 0)
	{
		buffer[bytes_read] = '\0';
		printf("%s", buffer);
	}
	if(bytes_read == -1)
	{
		// printf("error reading");
		read_errno = errno;
	}

	close(read_fd);
	read_fd = open(read_file_name, O_RDONLY);	
	if (read_fd == -1)
	{
		printf("could not open read_fd for reading");
	}
	printf("ft_read: ");
	while ((bytes_read = read(read_fd, buffer, BUF_SIZE - 1)) > 0)
	{
		buffer[bytes_read] = '\0';
		printf("%s", buffer);
	}
	if(bytes_read == -1)
	{
		// printf("error reading");
		ft_read_errno = errno;
	}
	remove(read_file_name);

	if (read_errno != 0)
	{
		printf("\nread errno:    %d\n", read_errno);
	}
	if (ft_read_errno != 0)
	{
		printf("ft_read errno: %d\n", ft_read_errno);
	}
}

void test_strdup()
{
	printf("\n%sFT_STRDUP%s\n", STAR, STAR);
	char *str = "Hello this is going to be dupstr";

	char *strdup_str = strdup(str);
	int ret = memcmp(str, strdup_str, strlen(str));
	int c_errno = errno;

	char *ft_strdup_str = ft_strdup(str);
	int ft_ret = memcmp(str, strdup_str, strlen(str));
	int ft_errno = errno;

	printf("clib: %s\n  ft: %s\n", strdup_str, ft_strdup_str);
	printf("clib: %d\n  ft: %d\n", ret, ft_ret);
	printf("clib: %d\n  ft: %d\n", c_errno, ft_errno);
}

int main(void)
{
	// Create long string
	char long_string[1046];
	for (int i = 0; i < 1046; ++i)
	{
		long_string[i] = '.';
	}
	long_string[1046] = '\0';

	test_strlen(long_string);
	test_strcpy(long_string);
	test_strcmp(long_string, long_string);
	/* test_write();
	test_read();
	test_strdup(); */
	return EXIT_SUCCESS;
}
