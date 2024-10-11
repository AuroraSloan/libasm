#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define STAR "****************"
#define BUF_SIZE 3

extern size_t ft_strlen(const char *s);
extern char *ft_strcpy(char *dst, const char*src);
extern int ft_strcmp(const char *s1, const char *s2);
extern ssize_t ft_write(int fd, const void *buff, size_t size);
extern ssize_t ft_read(int fd, const void *buff, size_t count);
extern char *ft_strdup(const char *s);

/**************FT_STRLEN*****************/
void test_strlen()
{
	printf("%sFT_STRLEN%s\n", STAR, STAR);
	printf("|  clib   |   ft  |\n");
	printf("|=================|\n");
	char *strlenstr = "";
	size_t len = strlen(strlenstr);
	size_t ft_len = ft_strlen(strlenstr);
	printf("|   %zu     |   %zu   |\n", len, ft_len);
}

/**************FT_STRCPY*****************/
void test_strcpy()
{
	printf("\n%sFT_STRCPY%s\n", STAR, STAR);
	char *strcpysrc = "yoyoyoyoyo ;laksjd fei";
	char *strcpydst = (char *)malloc(strlen(strcpysrc) + 1);
	printf("dst address: %p\n", (void *)strcpydst);

	memset(strcpydst, '\0', strlen(strcpydst));
	printf("before: %s\n", strcpydst);
	char *strcpyret = strcpy(strcpydst, strcpysrc);
	printf("%p | %s\n", (void *)strcpyret, strcpydst);

	memset(strcpydst, '\0', strlen(strcpydst));
	printf("before: %s\n", strcpydst);
	char *ft_strcpyret = ft_strcpy(strcpydst, strcpysrc);
	printf("%p | %s\n", (void *)ft_strcpyret, strcpydst);
}

/**************FT_STRCMP*****************/
void test_strcmp()
{
	printf("\n%sFT_STRCMP%s\n", STAR, STAR);
	char *cmp1 = "aaaaaaaasaaa";
	char *cmp2 = "aaaaaaaaaaaa";

	int ret = strcmp(cmp1, cmp2);
	int ft_ret = ft_strcmp(cmp1, cmp2);
	
	printf("|  clib   |   ft  |\n");
	printf("|=================|\n");
	printf("|   %d     |   %d   |\n", ret, ft_ret);
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
	test_strlen();
	test_strcpy();
	test_strcmp();
	test_write();
	test_read();
	test_strdup();
	return EXIT_SUCCESS;
}
