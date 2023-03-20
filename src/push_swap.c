/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsusanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:50:59 by fsusanna          #+#    #+#             */
/*   Updated: 2023/03/13 23:32:47 by fsusanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	ft_atoi(char *str, int *err)
{
	unsigned int	ret;
	unsigned int	max;
	int	sign;

	max = (1 << (8 * sizeof(ret) - 1)) - 1U;
	while (' ' == *str)
		str++;
	sign = 1;
	if ('-' == *str)
		sign = -1;
	if ('-' == *str || '+' == *str)
		str++;
	ret = 0;
	while (!(*err) && *str >= '0' && *str <= '9')
	{
		ret = ret * 10 + (*(str++) - '0');
		if (ret > max + (1 - sign) / 2)
			*err = -1;
	}
	if (*str || '+' == *(str - 1) || '-' == *(str - 1))
		*err = -1;
	return (sign * ret);
}

void	index(t_data **stk)
{
	t_data	*tmp;

	tmp = (t_data *)&((*stk)[(*stk)[0].head[0]].id);
	tmp->target = 0;
	tmp = (t_data *)&((*stk)[tmp->next].id);
	while(tmp != (t_data *)&((*stk)[(*stk)[0].head[0]].id))
	{
		tmp->target = (*stk)[tmp->prev].target + 1;
		tmp = (t_data *)&((*stk)[tmp->next].id);
	}
}

void	ft_move_data(t_data **stk, int mv, int on)
{
	if ((*stk)[mv].id > -1)
	{
		(*stk)[(*stk)[mv].next].prev = (*stk)[mv].prev;
		(*stk)[(*stk)[mv].prev].next = (*stk)[mv].next;
	}
	(*stk)[mv].id = (*stk)[on].id;
	(*stk)[mv].prev = stk[on]->prev;
	(*stk)[mv].next = on;
	(*stk)[on].prev = mv;
	(*stk)[(*stk)[mv].prev].next = mv;
}

void	init(t_data **stk, int n, int val, int *err)
{
	int	i;

	printf("Val %d: %d\n", n, val);
	printf("puntero stk: %p\n", stk);
	printf("puntero *stk: %p\n", *stk);
	printf("puntero (*stk)+1: %p\n", (*stk) + 1);
	printf("puntero stk + 1: %p\n", stk + 1);
	printf("puntero stk[n]: %p\n", stk[n]);
	(*stk)[n].val = val;
	if (!n)
	{
		(*stk)[n].id = 0;
		(*stk)[n].head[0] = 0;
		(*stk)[n].prev = 0;
		(*stk)[n].next = 0;
	}
	else
	{
		printf("aquí0\n");
		(*stk)[n].id = -1;
		i = 0;
		printf("aquí1\n");
		while (val <= (*stk)[(*stk)[i].prev].val && (*stk)[i].val > (*stk)[(*stk)[i].prev].val)
			i = (*stk)[i].prev;
		while (val > (*stk)[i].val && (*stk)[i].val > (*stk)[(*stk)[i].prev].val)
			i = (*stk)[i].next;
		printf("aquí2\n");
		if ((*stk)[i].val == val)
			*err = -1;
		ft_move_data(stk, n, i);
		if ((*stk)[(*stk)[n].head[0]].val > val)
			(*stk)[n].head[0] = n;
	}
}

int	main(int narg, char **args)
{
	int	err;
	int	i;
	t_data	*stack;
	int	head[2];
	char	txt[5] = "1234\n";

	printf("txt: %p\n", txt);
	printf("&txt: %p\n", &txt);

	stack = malloc((narg - 1) * sizeof(t_data));
	i = 0;
	err = 0;
	head[0] = -1;
	head[1] = -1;
	if (!(stack))
		err = -1;
	printf("     head: %p\n", head);
	printf("  head[0]: %i\n", head[0]);
	printf("    *head: %i\n", *head);
	printf(" &head[0]: %p\n", &head[0]);
	while (!err && ++i < narg)
	{
		printf("i = %i\n", i);
		stack[i - 1].head = &head[0];
		init(&stack, i - 1, ft_atoi(args[i], &err), &err);
	}
	if (narg != i)
		write(1, "Error\n", 6);
	else
	{
		index(&stack);
		process(&stack, narg);
	}
	free(stack);
	return (0);
}
