/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsusanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:50:59 by fsusanna          #+#    #+#             */
/*   Updated: 2023/04/27 03:07:57 by fsusanna         ###   ########.fr       */
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

void	add_data(t_compendium *all, int position, t_data *on)
{
	t_data	*mv;

	mv = &(all->s[position]);
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
	if (!all->top[0] || mv->val < all->top[0]->val)
		all->top[0] = mv;
}

void	init(t_compendium *all, int narg, char **args, int *err)
{
	t_data	*i;
	int		n;
	int		val;

	n = 0;
	while (!(*err) && ++n < narg)
	{
		val = ft_atoi(args[n], err);
		if (*err)
			break ;
		all->s[n - 1].val = val;
		all->s[n - 1].id = -1;
		i = NULL;
		if (n > 1)
		{
			i = all->top[0];
			while (val > i->val && (i->val > i->prev->val || val < i->prev->val))
				i = i->next;
			if (i->val == val)
				*err = -1;
		}
		add_data(all, n - 1, i);
	}
	if (!(*err))
		index(all);
}

int	main(int narg, char **args)
{
	int	err;
	t_compendium	all;
	t_data			*stack;
	t_data			*top[2];

	setvbuf(stdout, NULL, _IONBF, 0);
	err = 0;
	stack = malloc((narg - 1) * sizeof(t_data));
	if (stack && narg > 1)
	{
		all.count_val = narg - 1;
		all.top = top;
		all.s = stack;
		top[0] = all.s;
		top[1] = NULL;
		init(&all, narg, args, &err);
	}
	if (!stack || err)
		write(1, "Error\n", 6);
	else
		start(&all);
	free(stack);
	return (0);
}