/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsusanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:50:59 by fsusanna          #+#    #+#             */
/*   Updated: 2023/09/28 09:43:09 by fsusanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	main(int narg, char **args)
{
	int				num;
	int				err;
	int				i;
	t_compendium	all;
	t_data			*top[2];

	num = count_vals(narg, args);
	all.s = malloc((num) * sizeof(t_data));
	err = 0;
	if (!all.s)
		err = -1;
	all.count_val = 0;
	all.top = top;
	all.top[0] = all.s;
	all.top[1] = NULL;
	i = 0;
	while (!err && ++i < narg)
		init(&all, args[i], &err);
	all.count_golden = phi(all.count_val);
	if (all.count_val != num || err)
		write(2, "Error\n", 6);
	if (!err && all.count_val == num && num > 1)
		start(&all);
	free(all.s);
	return (0);
}
