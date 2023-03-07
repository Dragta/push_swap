/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsusanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:50:59 by fsusanna          #+#    #+#             */
/*   Updated: 2023/03/07 10:52:34 by fsusanna         ###   ########.fr       */
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

int	main(int narg, char **args)
{
	int	err;
	int	i;
	int	n;
	int	*data;

	data = malloc(narg * sizeof(int));
	i = 1;
	if (!data)
		i = narg + 1;
	while (narg > i)
	{
		err = 0;
		n = ft_atoi(args[i], &err);
		if (err)
			break;
		data[i - 1] = n;
		i++;
	}
	if (narg != i)
		write(1, "Error\n", 6);
	else
		process(data, narg);
	free(data);
	return (0);
}
