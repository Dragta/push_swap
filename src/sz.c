#include <stdio.h>

typedef struct s_list
{
	int				val;
	int				initial;
	int				target;
	struct s_list	**top;
	struct s_list	*prev;
	struct s_list	*next;
}			t_list;

int	main(void)
{
	int	var;
	t_list	*prblst[2];

	printf("ptr prblst: %p\n", prblst);
	printf("ptr &prblst: %p\n", &prblst);
	printf("ptr prblst[0]: %p\n", prblst[0]);
	printf("ptr prblst[1]: %p\n", prblst[1]);
	printf("ptr &prblst[0]: %p\n", &prblst[0]);
	printf("ptr &prblst[1]: %p\n", &prblst[1]);
	printf("ptr &prblst[0] + 1: %p\n", &prblst[0] + 1);
	printf("ptr prblst[0] + 1: %p\n", prblst[0] + 1);
	return (0);
}
ptr prblst: 0x7ffdd30d02d0
ptr &prblst: 0x7ffdd30d02d0
ptr prblst[0]: (nil)
ptr prblst[1]: 0x560c1a87c080
ptr &prblst[0]: 0x7ffdd30d02d0
ptr &prblst[1]: 0x7ffdd30d02d8
ptr &prblst[0] + 1: 0x7ffdd30d02d8
ptr prblst[0] + 1: 0x28
