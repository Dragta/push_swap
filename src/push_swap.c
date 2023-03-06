/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsusanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:50:59 by fsusanna          #+#    #+#             */
/*   Updated: 2023/03/06 20:11:41 by fsusanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	main(int narg, char **args)
{
	int	err;
	int	i;
	int	n;
	int	*data;

	data = malloc(narg * sizeof(int));
	if (!data)
		return (1);
	i = 1;
	while (narg > i)
	{
		err = 0;
		n = ft_atoi(args[i], &err);
		if (err)
			break;
		data[i - 1] = n;
		i++;
	}
	if (narg > i)
		write(1, "Error\n", 6);
	else
		order(data);
	free(data);
	return (0);
}
