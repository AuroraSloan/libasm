#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STAR "****************"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define RESET "\033[0m"

#define BASE2 "01"
#define BASE3 "012"
#define BASE5 "01234"
#define BASE7 "0123456"
#define BASE8 "01234567"
#define BASE10 "0123456789"
#define BASE12 "0123456789ab"
#define BASE16 "0123456789abcdef"
#define BASE20 "0123456789abcdefghij"
#define BASE30 "0123456789abcdefghijklmnopqrst"
#define BASE36 "0123456789abcdefghijklmnopqrstuvwxy@"

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

/***************    ATOI    *****************/
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
	compare_atoi_base("12354", "8", 0);
	compare_atoi_base("12354", "11", 0);
	compare_atoi_base("12354", "1234256", 0);
	compare_atoi_base("!!", BASE2, 0);
	compare_atoi_base("", BASE2, 0);

	printf("base 2 ----------\n");
	compare_atoi_base("00000001", BASE2, 1);
	compare_atoi_base("1010", BASE2, 10);
	compare_atoi_base("-1010", BASE2, -10);
	compare_atoi_base("11111111", BASE2, 255);
	compare_atoi_base("     +11111111", BASE2, 255);

	printf("base 3 ----------\n");
	compare_atoi_base("102", BASE3, 11);
	compare_atoi_base("-102", BASE3, -11);
	compare_atoi_base("  	-102", BASE3, -11);

	printf("base 5 ----------\n");
	compare_atoi_base("304", BASE5, 79);
	compare_atoi_base("-304", BASE5, -79);
	compare_atoi_base(" 304", BASE5, 79);

	printf("base 7 ----------\n");
	compare_atoi_base("123", BASE7, 66);
	compare_atoi_base("-123", BASE7, -66);
	compare_atoi_base("      -123", BASE7, -66);

	printf("base 8 ----------\n");
	compare_atoi_base("144", BASE8, 100);
	compare_atoi_base("-144", BASE8, -100);
	compare_atoi_base("377", BASE8, 255);

	printf("base 10 ----------\n");
	compare_atoi_base("12345", BASE10, 12345);
	compare_atoi_base("-12345", BASE10, -12345);
	compare_atoi_base("2147483647", BASE10, 2147483647);
	compare_atoi_base("--+9832", BASE10, 9832);
	compare_atoi_base("-+-9832", BASE10, 9832);
	compare_atoi_base("-+-+9832", BASE10, 9832);
	compare_atoi_base("    -+--+8323aaas333", BASE10, -8323);
	compare_atoi_base("	-+--+8323aaas333", BASE10, -8323);

	printf("base 12 ----------\n");
	compare_atoi_base("a5", BASE12, 125);
	compare_atoi_base("-a5", BASE12, -125);

	printf("base 16 ----------\n");
	compare_atoi_base("1a3f", BASE16, 6719);
	compare_atoi_base("-1a3f", BASE16, -6719);

	printf("base 20 ----------\n");
	compare_atoi_base("j9", BASE20, 389);
	compare_atoi_base("-j9", BASE20, -389);

	printf("base 30 ----------\n");
	compare_atoi_base("t5", BASE30, 875);
	compare_atoi_base("-t5", BASE30, -875);

	printf("base 36 ----------\n");
	compare_atoi_base("@", BASE36, 35);
	compare_atoi_base("-@", BASE36, -35);
}

/***************    LIST TEST UTILS    *****************/
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

int is_correct_size(t_list *list, int size)
{
	return (ft_list_size(list) == size);
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
	printf("%sPASS%s\n", GREEN, RESET);
}

/***************    PUSH & SIZE TESTS    *****************/
void check_push_and_size(t_list *list, char *word, int size)
{
	char *first_word = (char *)list->data;
	if (is_correct_size(list, size) && strcmp(first_word, word) == 0)
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

	printf("\n%s PUSH FRONT & SIZE %s\n", STAR, STAR);
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
	ft_list_push_front(NULL, NULL);
	check_push_and_size(*list, order, 7);
}

/***************    SORT TESTS   *****************/
void test_sort(t_list **list)
{
	printf("\n%s SORT %s\n", STAR, STAR);
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

	// sort
	ft_list_sort(list, strcmp);
	check_list_items(*list, abc_order);

	// edge cases
	ft_list_sort(NULL, strcmp);
	ft_list_sort(NULL, NULL);
	ft_list_sort(list, NULL);
	ft_list_sort(list, strcmp); // already sorted list
	check_list_items(*list, abc_order);
}

/***************    REMOVE    *****************/
void check_size(t_list *list, int size)
{
	if (is_correct_size(list, size))
	{
		printf("%sPASS%s\n", GREEN, RESET);
		return;
	}
	printf("%sFAIL%s\n", RED, RESET);
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

	printf("\n%s REMOVE IF %s\n", STAR, STAR);

	/**** TEST SIZE ****/ 
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

	/**** TEST CONTENT ****/
	check_list_items(*list, abc_order);
}

int main(void)
{
	t_list *list;
	list = NULL;	
	char nottwo[] = "not";
	char ordertwo[] = "order";

	test_atoi_base();
	test_push_and_size(&list);
	// print_list(list);
	ft_list_push_front(&list, nottwo); // add duplicate item
	ft_list_push_front(&list, ordertwo); // add duplicate item
	// printf("\n\n");
	// print_list(list);
	test_sort(&list);
	// print_list(list);
	test_remove(&list);
	// print_list(list);
	clear_list(list);
	return EXIT_SUCCESS;
}
