#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

	compare_atoi_base("12354", "", 0);
	compare_atoi_base("12354", "1", 0);
	compare_atoi_base("12354", "37", 0);

	printf("base 2 ----------\n");
	compare_atoi_base("00000001", "2", 1);
	compare_atoi_base("1010", "2", 10);
	compare_atoi_base("-1010", "2", -10);
	compare_atoi_base("11111111", "2", 255);
	compare_atoi_base("     +11111111", "2", 255);

	printf("base 3 ----------\n");
	compare_atoi_base("102", "3", 11);
	compare_atoi_base("-102", "3", -11);
	compare_atoi_base("  	-102", "3", -11);

	printf("base 5 ----------\n");
	compare_atoi_base("304", "5", 79);
	compare_atoi_base("-304", "5", -79);
	compare_atoi_base(" 304", "5", 79);

	printf("base 7 ----------\n");
	compare_atoi_base("123", "7", 66);
	compare_atoi_base("-123", "7", -66);
	compare_atoi_base("      -123", "7", -66);

	printf("base 8 ----------\n");
	compare_atoi_base("144", "8", 100);
	compare_atoi_base("-144", "8", -100);
	compare_atoi_base("377", "8", 255);

	printf("base 10 ----------\n");
	compare_atoi_base("12345", "10", 12345);
	compare_atoi_base("-12345", "10", -12345);
	compare_atoi_base("2147483647", "10", 2147483647);
	compare_atoi_base("--+9832", "10", 9832);
	compare_atoi_base("-+-9832", "10", 9832);
	compare_atoi_base("-+-+9832", "10", 9832);
	compare_atoi_base("   -+--+8323aaas333", "10", -8323);

	printf("base 12 ----------\n");
	compare_atoi_base("A5", "12", 125);
	compare_atoi_base("-A5", "12", -125);

	printf("base 16 ----------\n");
	compare_atoi_base("1A3F", "16", 6719);
	compare_atoi_base("-1A3F", "16", -6719);

	printf("base 20 ----------\n");
	compare_atoi_base("J9", "20", 389);
	compare_atoi_base("-J9", "20", -389);

	printf("base 30 ----------\n");
	compare_atoi_base("T5", "30", 875);
	compare_atoi_base("-T5", "30", -875);

	printf("base 36 ----------\n");
	compare_atoi_base("Z", "36", 35);
	compare_atoi_base("-Z", "36", -35);
}

void clear_list(t_list *list)
{
	t_list *node = NULL;
	while (list)
	{
		node = list;
		list = list->next;
		free(node);
	}
}

void print_list(t_list *list)
{
	t_list *lst = list;
	while (lst)
	{
		printf("%s\n", (char *)lst->data);
		lst = lst->next;
	}
}

void check_push_and_size(t_list *list, char *word, int size)
{
	char *first_word = (char *)list->data;
	if (ft_list_size(list) == size && strcmp(first_word, word) == 0)
	{
		printf("%sPASS%s\n", GREEN, RESET);
		return;
	}
	printf("%sFAIL%s\n", RED, RESET);
}

void check_size_edgecase(t_list *list)
{
	if (ft_list_size(list) == 0
		&& ft_list_size(NULL) == 0)
	{
		printf("%sPASS%s\n", GREEN, RESET);
		return;
	}
	printf("%sFAIL%s\n", RED, RESET);
}

void test_push_and_size(t_list **list)
{
	char *hey = "hey";
	char *this = "this";
	char *is = "is";
	char *not = "not";
	char *in = "in";
	char *abc = "alphabetical";
	char *order = "order";

	printf("\n%sFT_LIST_PUSH_FRONT%s\n", STAR, STAR);
	check_size_edgecase(*list);
	ft_list_push_front(list, hey);
	check_push_and_size(*list, hey, 1);
	ft_list_push_front(list, this);
	check_push_and_size(*list, this, 2);
	ft_list_push_front(list, is);
	check_push_and_size(*list, is, 3);
	ft_list_push_front(NULL, hey);
	ft_list_push_front(list, not);
	check_push_and_size(*list, not, 4);
	ft_list_push_front(list, in);
	check_push_and_size(*list, in, 5);
	ft_list_push_front(list, NULL);
	ft_list_push_front(list, abc);
	check_push_and_size(*list, abc, 6);
	ft_list_push_front(list, order);
	check_push_and_size(*list, order, 7);
	ft_list_push_front(NULL, NULL);
}

void check_list_order(t_list *list)
{
	t_list *lst = list;
	int i = 0;
	char *abc_order[] = {
		"alphabetical",
		"hey",
		"in",
		"is",
		"not",
		"not",
		"order",
		"order",
		"this",
	};

	while (lst)
	{
		if (strcmp(lst->data, abc_order[i++]) != 0)
		{
			printf("%sFAIL%s\n", RED, RESET);
			return;
		}
		lst = lst->next;
	}
	printf("%d items - %sPASS%s\n", i, GREEN, RESET);
}

void test_sort(t_list **list)
{

	ft_list_sort(list, strcmp);
	check_list_order(*list);
	ft_list_sort(NULL, strcmp);
	check_list_order(*list);
	ft_list_sort(NULL, NULL);
	check_list_order(*list);
	ft_list_sort(list, NULL);
	check_list_order(*list);
	ft_list_sort(list, strcmp); // already sorted list
	check_list_order(*list);
}

void check_size(t_list *list, int size)
{
	if (ft_list_size(list) == size)
	{
		printf("%sPASS%s\n", GREEN, RESET);
		return;
	}
	printf("%sFAIL%s\n", RED, RESET);
}

void check_list_items(t_list *list, char **abc_order)
{
	t_list *lst = list;
	int i = 0;

	while (lst)
	{
		if (!abc_order[i] || strcmp(lst->data, abc_order[i++]) != 0)
		{
			printf("%sFAIL%s\n", RED, RESET);
			return;
		}
		lst = lst->next;
	}
	printf("%d items - %sPASS%s\n", i, GREEN, RESET);
}

void test_remove(t_list **list)
{
	char *abc_order[] = {
		"hey",
		"in",
		"is",
		"order",
		"order"
	};

	check_size(*list, 9);
	// remove first item
	ft_list_remove_if(list, "alphabetical", strcmp, free);
	check_size(*list, 8);
	// remove last item
	ft_list_remove_if(list, "this", strcmp, free);
	check_size(*list, 7);
	// remove duplicate item
	ft_list_remove_if(list, "not", strcmp, free);
	check_size(*list, 5);

	//edge cases 
	ft_list_remove_if(NULL, "not", strcmp, free);
	check_size(*list, 5);
	ft_list_remove_if(list, NULL, strcmp, free);
	check_size(*list, 5);
	ft_list_remove_if(list, "not", NULL, free);
	check_size(*list, 5);
	ft_list_remove_if(list, "not", strcmp, NULL);
	check_size(*list, 5);

	print_list(*list);
	check_list_items(*list, abc_order);
}

int main(void)
{
	t_list *list;
	list = NULL;	
	char nottwo[] = "not";
	char ordertwo[] = "order";

	// test_atoi_base();
	test_push_and_size(&list);
	ft_list_push_front(&list, nottwo); // add duplicate item
	ft_list_push_front(&list, ordertwo); // add duplicate item
	test_sort(&list);
	print_list(list);
	test_remove(&list);
	clear_list(list);
	return EXIT_SUCCESS;
}
