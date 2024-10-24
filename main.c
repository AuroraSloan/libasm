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
#define BUF_SIZE 1046
#define C_FILE "c_file.txt"
#define FT_FILE "ft_file.txt"

extern size_t ft_strlen(const char *s);
extern char *ft_strcpy(char *dst, const char*src);
extern int ft_strcmp(const char *s1, const char *s2);
extern ssize_t ft_write(int fd, const void *buff, size_t size);
extern ssize_t ft_read(int fd, const void *buff, size_t count);
extern char *ft_strdup(const char *s);

typedef struct		s_rwinfo
{
	int	fd;
	int	ft_fd;
	ssize_t wbytes;
	ssize_t ft_wbytes;
	ssize_t	rbytes;
	ssize_t	ft_rbytes;
	int	c_errno;
	int	ft_errno;
	char	buf[BUF_SIZE];
	char	ft_buf[BUF_SIZE];
	char	*s;
	char	*ft_s;
}			t_rwinfo;

int prnt_err(const char *s)
{
	fprintf(stderr, "%s%s%s\n",s , RED, RESET);
	return EXIT_FAILURE;
}

void close_and_rm_file(int fd, char *file_name)
{	
	if (close(fd) < 0)
	{
		prnt_err("Could not close file\n");
		return;
	}
	if (remove(file_name) < 0)
	{
		prnt_err("Could not remove file\n");
	}
}

void close_and_rm_files(t_rwinfo info)
{
	close_and_rm_file(info.fd, C_FILE);
	close_and_rm_file(info.ft_fd, FT_FILE);
}

int open_files(t_rwinfo *info)
{
	info->fd = open(C_FILE, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	info->ft_fd = open(FT_FILE, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	if (info->fd < 0 || info->ft_fd < 0)
	{
		if (info->ft_fd < 0)
		{
			close_and_rm_file(info->fd, C_FILE);
		}
		return prnt_err("Could not open file\n");
	}
	return EXIT_SUCCESS;
}

ssize_t write_to_file(ssize_t (*wrt_fnc)(int, const void*, size_t), int fd, const char *s)
{
	int len = 0;

	if (s)
	{
		len = strlen(s);
	}
	return wrt_fnc(fd, s, len);
}

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
		prnt_err("malloc failed\n");
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

	if ((ret < 0 && ft_ret < 0)
		|| (ret > 0 && ft_ret > 0)
		|| (ret == 0 && ft_ret == 0))
	{
		printf("%sPASS%s\n", GREEN, RESET);
		return;
	}
	printf("%sFAIL%s : ret %d : ft %d\n", RED, RESET, ret, ft_ret);
	
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
void compare_write_results(t_rwinfo info)
{
	if (info.wbytes == info.ft_wbytes && info.c_errno == info.ft_errno)
	{
		printf("%sPASS%s\n", GREEN, RESET);
	}
	else
	{
		printf("%sFAIL%s\n", RED, RESET);
	}
}

void write_to_files(t_rwinfo *info, const char *s)
{
	errno = 0;
	info->wbytes = write_to_file(write, info->fd, s);
	info->c_errno = errno;

	errno = 0;
	info->ft_wbytes = write_to_file(ft_write, info->ft_fd, s);
	info->ft_errno = errno;
}

int seek_file_start(t_rwinfo info)
{
	if (lseek(info.fd, 0, SEEK_SET) == (off_t) -1)
	{
		return prnt_err("Could not seek fd\n");
	}
	if (lseek(info.ft_fd, 0, SEEK_SET) == (off_t) -1)
	{
		return prnt_err("Could not seek ft_fd\n"); 
	}
	return EXIT_SUCCESS;
}

int compare_write_files(t_rwinfo *info)
{
	while (1)
	{
		info->rbytes = read(info->fd, info->buf, BUF_SIZE);
		info->ft_rbytes = read(info->ft_fd, info->ft_buf, BUF_SIZE);

		if (info->rbytes == 0 && info->ft_rbytes == 0)
		{
			break;
		}

		if (info->rbytes < 0 || info->ft_rbytes < 0)
		{
			return prnt_err("read failed\n");
		}

		if (info->rbytes != info->ft_rbytes
			|| memcmp(info->buf, info->ft_buf, (size_t)info->rbytes) != 0)
		{
			printf("%sFAIL%s\n", RED, RESET);
			return EXIT_FAILURE;
		}
	}
	return EXIT_SUCCESS;
}

void compare_write(const char *s)
{
	t_rwinfo info;
	memset(&info, 0, sizeof(t_rwinfo));


	if (open_files(&info) < 0)
	{
		return;
	}

	write_to_files(&info, s);	
	if (info.wbytes < 0 || info.ft_wbytes < 0)
	{
		compare_write_results(info);
		return close_and_rm_files(info);
	}

	if (seek_file_start(info) < 0 || compare_write_files(&info) < 0)
	{
		return close_and_rm_files(info);
	}

	compare_write_results(info);
	close_and_rm_files(info);
}

void compare_invalid_fd()
{
	t_rwinfo info;
	memset(&info, 0, sizeof(t_rwinfo));
	info.fd = -1;
	info.ft_fd = -1;
	write_to_files(&info, "HEY");
	compare_write_results(info);
}

void write_to_terminal(int fd, const char *s)
{
	t_rwinfo info;
	memset(&info, 0, sizeof(t_rwinfo));
	info.wbytes = write(fd, s, strlen(s));
	info.ft_wbytes = ft_write(fd, s, strlen(s));
	compare_write_results(info);
}

void test_write(const char *long_string)
{
	printf("\n%sFT_WRITE%s\n", STAR, STAR);
	compare_write("Hello, this is a string");
	compare_write("a");
	compare_write("");
	compare_write(long_string);
	compare_write("Hello, this string has a new line\n and a \ttab");
	compare_write("escaping this\0string");
	compare_write(NULL);
	compare_invalid_fd();
	write_to_terminal(1, "Hello, this is a string out\n");
	write_to_terminal(2, "Hello, this is a string err\n");
}

/**************FT_READ*****************/

void compare_read_results(t_rwinfo info)
{
	if (info.rbytes == info.ft_rbytes && info.c_errno == info.ft_errno)
	{
		printf("%sPASS%s\n", GREEN, RESET);
	}
	else
	{
		printf("%sFAIL%s\n", RED, RESET);
	}
}

int write_to_read_files(t_rwinfo *info, const char *s)
{
	info->wbytes = write_to_file(write, info->fd, s);
	info->ft_wbytes = write_to_file(write, info->ft_fd, s);
	if (info->wbytes < 0 || info->ft_wbytes < 0)
	{	
		return prnt_err("unable to write to files\n");
	}
	return EXIT_SUCCESS;
}

int compare_read_files(t_rwinfo *info)
{
	while (1)
	{
		errno = 0;
		info->rbytes = read(info->fd, info->buf, BUF_SIZE);
		info->c_errno = errno;
		errno = 0;
		info->ft_rbytes = ft_read(info->ft_fd, info->ft_buf, BUF_SIZE);
		info->ft_errno = errno;

		if (info->rbytes == 0 && info->ft_rbytes == 0)
		{
			break;
		}

		if (info->rbytes < 0 || info->ft_rbytes < 0)
		{
			compare_read_results(*info);
			return EXIT_FAILURE;
		}	

		if (info->rbytes != info->ft_rbytes
			|| memcmp(info->buf, info->ft_buf, (size_t)info->rbytes) != 0)
		{
			printf("%sFAIL%s\n", RED, RESET);
			return EXIT_FAILURE;
		}
	}
	return EXIT_SUCCESS;
}

void compare_read(const char *s)
{
	t_rwinfo info;
	memset(&info, 0, sizeof(t_rwinfo));

	if (open_files(&info) < 0)
	{
		return;
	}

	if (write_to_read_files(&info, s) < 0)
	{
		return close_and_rm_files(info);
	}

	if (seek_file_start(info) < 0 || compare_read_files(&info) < 0)
	{
		return close_and_rm_files(info);
	}

	compare_read_results(info);
	close_and_rm_files(info);
}

void test_read(const char *long_string)
{
	printf("\n%sFT_READ%s\n", STAR, STAR);
	compare_read("Hello, this is a string");
	compare_read("a");
	compare_read("");
	compare_read(long_string);
	compare_read("Hello, this string has a new line\n and a \ttab");
	compare_read("escaping this\0string");
	compare_read(NULL);
}

/**************FT_STRDUP*****************/

void free_strings(t_rwinfo info)
{
	free(info.s);
	free(info.ft_s);
}

void compare_strdup(const char *s)
{
	t_rwinfo info;
	memset(&info, 0, sizeof(t_rwinfo));
	int len = strlen(s) + 1;

	info.s = strdup(s);
	info.ft_s = ft_strdup(s);
	if (info.s == NULL)
	{
		prnt_err("could not allocate memory\n");
		return;
	}
	if (info.ft_s == NULL)
	{
		free(info.s);
		prnt_err("could not allocate memory\n");
		return;
	}	

	if (memcmp(info.s, info.ft_s, len) != 0)
	{
		printf("%sFAIL%s\n", RED, RESET);
		free_strings(info);
		return;
	}
	
	printf("%sPASS%s\n", GREEN, RESET);
	free_strings(info);
}

void test_strdup(const char *long_string)
{
	printf("\n%sFT_STRDUP%s\n", STAR, STAR);
	compare_strdup("Hello, this is a string");
	compare_strdup("a");
	compare_strdup("");
	compare_strdup(long_string);
	compare_strdup("Hello, this string has a new line\n and a \ttab");
	compare_strdup("escaping this\0string");
}

int main(void)
{
	char long_string[1046];
	memset(long_string, '.', 1045);
	long_string[1045] = '\0';

	test_strlen(long_string);
	test_strcpy(long_string);
	test_strcmp(long_string, long_string);
	test_write(long_string);
	test_read(long_string);
	test_strdup(long_string);
	return EXIT_SUCCESS;
}
