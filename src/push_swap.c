/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsusanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:50:59 by fsusanna          #+#    #+#             */
/*   Updated: 2023/03/28 02:35:16 by fsusanna         ###   ########.fr       */
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

	tmp = stk[0]->top[0];
	tmp->target = 0;
	tmp = tmp->next;
	i = 1;
	while(tmp != stk[0]->top[0])
	{
		tmp->target = i++;
		tmp = tmp->next;
	}
	printf("total i= %i\n", i);
	stk[0]->prev = stk[i - 1];
	stk[i - 1]->next = stk[0];
	while (--i)
	{
		stk[i]->prev = stk[i - 1];
		stk[i - 1]->next = stk[i];
	}
	stk[0]->top[0] = stk[0];
}

void	add_data(t_data *mv, t_data *on)
{
	mv->id = 0;
	if (!on)
	{
		mv->prev = mv;
		mv->next = mv;
	}
	else
	{
		mv->prev = on->prev;
		mv->next = on;
		on->prev = mv;
		mv->prev->next = mv;
	}
	if (!mv->top[0] || mv->val < mv->top[0]->val)
		mv->top[0] = mv;
}

void	init(t_data **stk, t_data *n, int val, int *err)
{
	t_data	*i;

	n->val = val;
	n->id = -1;
	i = stk[0]->top[0];
	if (n > stk[0])
	{
		while (val > i->val && (i->val > i->prev->val || val < i->prev->val))
			i = i->next;
		if (i->val == val)
			*err = -1;
	}
	add_data(n, i);
}

t_data	**mem_stack(int n)
{
	t_data	**ret;

	ret = malloc(n * sizeof(t_data *));
	if (ret)
	{
		*ret = malloc(n * sizeof(t_data));
		if (!(*ret))
		{
			free (ret);
			return (NULL);
		}
		while (--n)
			*(ret + n) = *ret + n;
	}
	return (ret);
}

int	main(int narg, char **args)
{
	int	err;
	int	i;
	t_data	**stack;
	t_data	*top[2];

	i = 0;
	err = 0;
	top[0] = NULL;
	top[1] = NULL;
	stack = mem_stack(narg - 1);
	if (!stack)
		err = -1;
	while (!err && ++i < narg)
	{
		printf("i = %i\n", i);
		stack[i - 1]->top = top;
		init(stack, stack[i - 1], ft_atoi(args[i], &err), &err);
		show_all(stack, i - 1);
	}
	if (narg != i)
		write(1, "Error\n", 6);
	else
	{
		index(stack);
		show_all(stack, i - 2);
		process(stack);
	}
	free(*stack);
	free(stack);
	return (0);
}
