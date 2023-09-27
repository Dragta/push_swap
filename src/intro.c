/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsusanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:50:59 by fsusanna          #+#    #+#             */
/*   Updated: 2023/09/27 17:52:21 by fsusanna         ###   ########.fr       */
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
	all->count_val++;
}

/*void	init(t_compendium *all, int position, int val, int *err)*/
void	init(t_compendium *all, char *arg, int *err)
{
	t_data	*i;
	int		position;
	int		v;

	v = ft_atoi(arg, err);
	while (!*err && *arg)
	{
		position = all->count_val;
		all->s[position].val = v;
		all->s[position].id = -1;
		i = NULL;
		if (position)
		{
			i = all->top[0];
			while (v > i->val && (i->val > i->prev->val || v <= i->prev->val))
				i = i->next;
			if (i->val == v)
				*err = -1;
		}
		add_data(all, position, i);
		arg++;
		while (arg[0] && (arg[-1] != ' ' || arg[0] == ' '))
			arg++;
		v = ft_atoi(arg, err);
	}
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
	if ((*str && *str != ' ') || '+' == *(str - 1) || '-' == *(str - 1))
		*err = -1;
	return (sign * ret);
}

int	count_vals(int narg, char **args)
{
	int	i;
	int	j;
	int	ret;

	ret = 0;
	i = 1;
	j = 0;
	while (i < narg)
	{
		if (args[i][j] != ' ' && (!args[i][j + 1] || args[i][j + 1] == ' '))
			ret++;
		j++;
		if (!args[i][j])
		{
			j = 0;
			i++;
		}
	}
	return (ret);
}
