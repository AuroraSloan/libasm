#include <stdio.h>
#include <stdlib.h>

#define STAR "****************"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define RESET "\033[0m"

typedef struct		s_list
{
	void		*data;
	struct s_list	*next;
}			t_list;

extern int 	ft_atoi_base(char *str, char *base);
extern void	ft_list_push_front(t_list **begin_list, void *data);
extern int	ft_list_size(t_list *begin_list);
extern void	ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(), void (*free_fct)(void*));
extern void	ft_list_sort(t_list **begin_list, int (*cmp)());

void compare_atoi_base(char *str, char *base, int cmp)
{
	int num = ft_atoi_base(str, base);
	if (num == cmp)
	{
		printf("%sPASS%s\n", GREEN, RESET);
		return;
	}
	printf("%sFAIL%s - %d\n", RED, RESET, num);
}

void test_atoi_base()
{
	printf("\n%sFT_ATOI_BASE%s\n", STAR, STAR);
	printf("base 2 ----------\n");
	compare_atoi_base("00000001", "2", 1);
	compare_atoi_base("1010", "2", 10);
	compare_atoi_base("-1010", "2", -10);
	compare_atoi_base("11111111", "2", 255);

	printf("base 3 ----------\n");
	compare_atoi_base("102", "3", 11);
	compare_atoi_base("-102", "3", -11);

	printf("base 5 ----------\n");
	compare_atoi_base("304", "5", 79);
	compare_atoi_base("-304", "5", -79);

	printf("base 7 ----------\n");
	compare_atoi_base("123", "7", 66);
	compare_atoi_base("-123", "7", -66);

	printf("base 8 ----------\n");
	compare_atoi_base("144", "8", 100);
	compare_atoi_base("-144", "8", -100);
	compare_atoi_base("377", "8", 255);

	printf("base 10 ----------\n");
	compare_atoi_base("12345", "10", 12345);
	compare_atoi_base("-12345", "10", -12345);
	// compare_atoi_base("2147483647", "10", -2147483648);

	printf("base 12 ----------\n");
	compare_atoi_base("A5", "12", 125);
	compare_atoi_base("-A5", "12", -125);

	printf("base 16 ----------\n");
	compare_atoi_base("1A3F", "16", 6719);
	compare_atoi_base("-1A3F", "16", -6719);
	// compare_atoi_base("FFFFFFFF", "16", 2147483647);

	printf("base 20 ----------\n");
	compare_atoi_base("J9", "20", 389);
	compare_atoi_base("-J9", "20", -389);

	printf("base 30 ----------\n");
	compare_atoi_base("T5", "30", 875);
	compare_atoi_base("-T5", "30", -875);

	printf("base 36 ----------\n");
	compare_atoi_base("Z", "36", 35);
	compare_atoi_base("-Z", "36", -35);
	// compare_atoi_base("ZZZZZZZZ", "36", 2821109907455);
}

int main(void)
{
	test_atoi_base();	
	return EXIT_SUCCESS;
}
