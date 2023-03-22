/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsusanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 15:29:40 by fsusanna          #+#    #+#             */
/*   Updated: 2023/03/13 22:18:38 by fsusanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_data
{
	int	id;
	int	*head;
	int	val;
	int	target;
	int	prev;
	int	next;
}			t_data;

int		ft_atoi(char *str, int *err);
void	index(t_data **stk);
void    ft_move_data(t_data **stk, int mv, int on);
void	init(t_data **stk, int n, int val, int *err);
void	process(t_data **stk, int n);
t_data	**mem_stack(int n);
int		main(int narg, char **args);
/*___Bonus part___*/
#endif
