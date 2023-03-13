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

void	init(t_list *stk, int n, int val, int *err)
{
	int	i;
	t_list	*new;

	new = stk + n;
	new->top = stk->top;
	*(new->top) = stk;
	new->val = val;
	new->initial = n;
	if (!n)
	{
		new->prev = stk;
		new->next = stk;
	}
	else
	{
		while (val <= stk->prev->val && stk->val > stk->prev->val)
			stk = stk->prev;
		while (val > stk->val && stk->val > stk->prev->val)
			stk = stk->next;
		if (stk->val == val)
			*err = -1;
		*(new->top) = NULL;
		ft_lstmove_on(new, stk);
	}
}

int	main(int narg, char **args)
{
	int	err;
	int	i;
	t_list	*stack_a;
	t_list	*top;

	stack_a = malloc((narg - 1) * sizeof(t_list));
	top = stack_a;
	i = 0;
	err = 0;
	if (!stack_a)
		err = 0;
	else
		stack_a->top = &top;
	while (!err && ++i < narg)
		init(stack_a, i - 1, ft_atoi(args[i], &err), &err);
	if (narg != i)
		write(1, "Error\n", 6);
	else
		process(stack_a);
	free(stack_a);
	return (0);
}
/*
int	main(int narg, char **args)
{
	int	err;
	int	i;
	int	n;
	int	*data;

	data = malloc(narg * sizeof(int));
	i = 0;
	if (!data)
		i = narg + 1;
	while (++i < narg)
	{
		err = 0;
		n = ft_atoi(args[i], &err);
		if (err)
			break ;
		data[i - 1] = n;
	}
	if (narg != i)
		write(1, "Error\n", 6);
	else
		process(data, narg);
	free(data);
	return (0);
}*/
