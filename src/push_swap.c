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
	int		i;

	i = 1;
	tmp = (t_data *)&((*stk)[(*stk)[0].head[0]].id);
	tmp->target = 0;
	tmp = (t_data *)&((*stk)[tmp->next].id);
	while(tmp != (t_data *)&((*stk)[(*stk)[0].head[0]].id))
	{
		tmp->target = (*stk)[tmp->prev].target + 1;
		tmp = (t_data *)&((*stk)[tmp->next].id);
		i++;
	}
	printf("total i= %i\n", i);
	(*stk)[0].prev = i - 1;
	(*stk)[i - 1].next = 0;
	while (--i)
	{
		(*stk)[i].prev = i - 1;
		(*stk)[i - 1].next = i;
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
	(*stk)[mv].prev = (*stk)[on].prev;
	(*stk)[mv].next = on;
	(*stk)[on].prev = mv;
	(*stk)[(*stk)[mv].prev].next = mv;
}

void	init(t_data **stk, int n, int val, int *err)
{
	int	i;

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
		(*stk)[n].id = -1;
		i = 0;
		while (val <= (*stk)[(*stk)[i].prev].val && (*stk)[i].val > (*stk)[(*stk)[i].prev].val)
			i = (*stk)[i].prev;
		while (val > (*stk)[i].val && ((*stk)[i].val > (*stk)[(*stk)[i].prev].val ||
			val < (*stk)[(*stk)[i].prev].val))
			i = (*stk)[i].next;
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

	stack = malloc((narg - 1) * sizeof(t_data));
	i = 0;
	err = 0;
	head[0] = -1;
	head[1] = -1;
	if (!(stack))
		err = -1;
	while (!err && ++i < narg)
	{
		printf("i = %i\n", i);
		stack[i - 1].head = &head[0];
		process(&stack, i - 1);
		init(&stack, i - 1, ft_atoi(args[i], &err), &err);
	}
	if (narg != i)
		write(1, "Error\n", 6);
	else
	{
		index(&stack);
		process(&stack, narg - 1);
	}
	free(stack);
	return (0);
}
