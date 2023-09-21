/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsusanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:50:59 by fsusanna          #+#    #+#             */
/*   Updated: 2023/09/18 18:09:39 by fsusanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	phi(int i)
{
	int	n2;
	int	n1;
	int	res;
	int	bit;
	int	sgn;

	sgn = 1;
	if (i < 0)
		sgn = -1;
	i *= sgn;
	bit = 13;
	n2 = 610;
	n1 = 377;
	res = 0;
	while (--bit >= 0)
	{
		if (i > n1)
		{
			res += 1 << bit;
			i -= n1;
		}
		n1 = n2 - n1;
		n2 = n2 - n1;
	}
	return (sgn * res);
}

void	add_data(t_compendium *all, int position, t_data *on)
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
		mv->prev->next = mv;
		mv->next = on;
		on->prev = mv;
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

int	ft_atoi(char *str, int *err)
{
	unsigned int	ret;
	unsigned int	max;
	int				sign;

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

int	main(int narg, char **args)
{
	int				err;
	int				i;
	t_compendium	all;
	t_data			*top[2];

	setvbuf(stdout, NULL, _IONBF, 0);
	err = 0;
	all.s = malloc((narg - 1) * sizeof(t_data));
	if (!all.s)
		err = -1;
	all.count_val = narg - 1;
	all.count_golden = phi(all.count_val);
	all.top = top;
	all.top[0] = all.s;
	all.top[1] = NULL;
	all.ops[1] = NULL;
	i = 0;
	while (!err && ++i < narg)
		init(&all, i - 1, ft_atoi(args[i], &err), &err);
	if (narg != i)
		write(2, "Error\n", 6);
	if (narg == i && narg > 2)
		start(&all);
	free(all.s);
	return (0);
}
