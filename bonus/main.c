#include <stdio.h>
#include <stdlib.h>

#define STAR "****************"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define RESET "\033[0m"

// extern int ft_atoi_base(char *str, char *base);
extern int ft_atoi_base(char *str, unsigned int base);

void compare_atoi_base(char *str, unsigned int base, int cmp)
{
	int num = ft_atoi_base(str, base);
	if (num == cmp)
	{
		printf("%sPASS%s\n", GREEN, RESET);
	}
	printf("%sFAIL%s - %d\n", RED, RESET, num);
	return;	
}

void test_atoi_base()
{
	printf("\n%sFT_ATOI_BASE%s\n", STAR, STAR);
	compare_atoi_base("-12345", 10, -12345);
	compare_atoi_base("12345", 10, 12345);
	compare_atoi_base("00000001", 2, 1);
}

int main(void)
{
	test_atoi_base();
	return EXIT_SUCCESS;
}
