#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define STAR "****************"

extern size_t ft_strlen(const char *s);
extern char *ft_strcpy(char *dst, const char*src);
extern int ft_strcmp(const char *s1, const char *s2);
extern ssize_t ft_write(int fd, const void *buff, size_t size);

int main(int argc, char **argv)
{
/**************FT_STRLEN*****************/
	printf("%sFT_STRLEN%s\n", STAR, STAR);
	printf("|  clib   |   ft  |\n");
	printf("|=================|\n");
	char *strlenstr = "";
	size_t len = strlen(strlenstr);
	size_t ft_len = ft_strlen(strlenstr);
	printf("|   %zu     |   %zu   |\n", len, ft_len);

/**************FT_STRCPY*****************/
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

/**************FT_STRCMP*****************/
	printf("\n%sFT_STRCMP%s\n", STAR, STAR);
	char *cmp1 = "aaaaaaaasaaa";
	char *cmp2 = "aaaaaaaaaaaa";

	int ret = strcmp(cmp1, cmp2);
	int ft_ret = ft_strcmp(cmp1, cmp2);
	
	printf("|  clib   |   ft  |\n");
	printf("|=================|\n");
	printf("|   %d     |   %d   |\n", ret, ft_ret);
/**************FT_WRITE*****************/
	printf("\n%sFT_WRITE%s\n", STAR, STAR);
	int fd = 2;
	char *str = "write this string\n";
	size_t write_len = strlen(str);

	/* write(2, "write:    ", 10);
	ssize_t bytes = write(fd, NULL, write_len);
	printf("errno: %d\n", errno); */

	write(2, "ft_write: ", 10);
	ssize_t ft_bytes = ft_write(fd, NULL, write_len);
	printf("errno: %d\n", errno);

	printf("|  clib   |   ft  |\n");
	printf("|=================|\n");
	// printf("|   %zd     |   %zd   |\n", bytes, ft_bytes);

/**************FT_READ*****************/
/**************FT_STRDUP*****************/
	return EXIT_SUCCESS;
}
