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

int	main(void)
{
	t_data	*stack;

	stack = malloc(5 * sizeof(t_data));

	printf("size t_data: %li\n", sizeof(t_data));
	printf("size: %li\n", sizeof(stack));
	printf("stack: %p\n", stack);
	printf("stack+1: %p\n", stack+1);
	free(stack);
	return (0);
}
