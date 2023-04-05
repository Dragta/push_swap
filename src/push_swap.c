/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsusanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:50:59 by fsusanna          #+#    #+#             */
/*   Updated: 2023/04/05 16:27:04 by fsusanna         ###   ########.fr       */
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
		tmp = tmp->next;
	}
	all->s[0]->prev = all->s[i - 1];
	all->s[i - 1]->next = all->s[0];
	while (--i)
	{
		all->s[i]->prev = all->s[i - 1];
		all->s[i - 1]->next = all->s[i];
	}
	set_top(all, all->s[0]);
}

void	add_data(t_compendium *all, t_data *mv, t_data *on)
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
	if (!all->top[0] || mv->val < all->top[0]->val)
		all->top[0] = mv;
}

void	init(t_compendium *all, t_data *n, int val, int *err)
{
	t_data	*i;

	n->val = val;
	n->id = -1;
	i = all->top[0];
	if (n > all->s[0])
	{
		while (val > i->val && (i->val > i->prev->val || val < i->prev->val))
			i = i->next;
		if (i->val == val)
			*err = -1;
	}
	add_data(all, n, i);
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
	t_compendium	all;
	t_data			**stack;
	t_data			*top[2];

	i = 0;
	err = 0;
	top[0] = NULL;
	top[1] = NULL;
	stack = mem_stack(narg - 1);
	if (!stack)
		err = -1;
	all.max_val = narg - 1;
	all.top = top;
	all.s = stack;
	while (!err && ++i < narg)
		init(&all, all.s[i - 1], ft_atoi(args[i], &err), &err);
	if (narg != i)
		write(1, "Error\n", 6);
	else
		start(&all);
	free(*stack);
	free(stack);
	return (0);
}
