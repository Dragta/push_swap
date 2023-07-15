/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsusanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:50:59 by fsusanna          #+#    #+#             */
/*   Updated: 2023/05/22 15:29:32 by fsusanna         ###   ########.fr       */
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

int	phi(int i)
{
	int	n2;
	int	n1;
	int	res;
	int	bit;

	bit = 12;
	n2 = 610;
	n1 = 377;
	res = 0;
	while (bit >= 0)
	{
		if (i > n1)
		{
			res += 1 << bit;
			i -= n1;
		}
		n1 = n2 - n1;
		n2 = n2 - n1;
		bit--;
	}
	return (res);
}

void	index(t_compendium *all)
{
	t_data	*tmp;
	int		i;

	tmp = all->top[0];
	tmp->target = 0;
	tmp = tmp->next;
	i = 1;
	while(tmp != all->top[0])
	{
		tmp->target = i++;
		tmp->golden = phi(i);
		tmp = tmp->next;
	}
	all->s[0].prev = &(all->s[i - 1]);
	all->s[i - 1].next = &(all->s[0]);
	while (--i)
	{
		all->s[i].prev = &(all->s[i - 1]);
		all->s[i - 1].next = &(all->s[i]);
	}
	all->top[0] = &(all->s[0]);
	count_stacks(all);
}

void	add_data(t_compendium *all, int position , t_data *on)
{
	t_data	*mv;

	mv = all->s + position;
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
	if (mv->val < all->top[0]->val)
		all->top[0] = mv;
}

void	init(t_compendium *all, int position, int val, int *err)
{
	t_data	*i;

	if (*err)
		return ;
	all->s[position].val = val;
	all->s[position].id = -1;
	i = NULL;
	if (position)
	{
		i = all->top[0];
		while (val > i->val && (i->val > i->prev->val || val < i->prev->val))
			i = i->next;
		if (i->val == val)
			*err = -1;
	}
	add_data(all, position, i);
}

int	main(int narg, char **args)
{
	int	err;
	int	i;
	t_compendium	all;
	t_data			*stack;
	t_data			*top[2];

	setvbuf(stdout, NULL, _IONBF, 0);
	err = 0;
	stack = malloc((narg - 1) * sizeof(t_data));
	if (!stack)
		err = -1;
	all.max_val = narg - 1;
	all.max_golden = phi(all.max_val);
	all.top = top;
	all.s = stack;
	top[0] = all.s;
	top[1] = NULL;
	i = 0;
	while (!err && ++i < narg)
		init(&all, i - 1, ft_atoi(args[i], &err), &err);
	if (narg != i)
		write(1, "Error\n", 6);
/*	if (narg == 3)
	{
		all.max[0] = 500;
		printf("mean: %i\n", mean(&all, 0));
	}*/
	if (narg == i && narg > 1)
		start(&all);
	free(stack);
	return (0);
}
