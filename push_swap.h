/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsusanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 15:29:40 by fsusanna          #+#    #+#             */
/*   Updated: 2023/03/28 02:19:04 by fsusanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_data
{
	int				id;
	struct s_data	**top;
	int				val;
	int				target;
	struct s_data	*prev;
	struct s_data	*next;
}			t_data;

int		ft_atoi(char *str, int *err);
void	index(t_data **stk);
void    data_atop(t_data *mv, t_data *on);
void	move_sa(t_data **stk);
void	move_sb(t_data **stk);
void	pr_sa(t_data **stk);
void	pr_sb(t_data **stk);
void	pr_ss(t_data **stk);
void	pr_pa(t_data **stk);
void	pr_pb(t_data **stk);
void	move_ra(t_data **stk);
void	move_rb(t_data **stk);
void	pr_ra(t_data **stk);
void	pr_rb(t_data **stk);
void	pr_rr(t_data **stk);
void	move_rra(t_data **stk);
void	move_rrb(t_data **stk);
void	pr_rra(t_data **stk);
void	pr_rrb(t_data **stk);
void	pr_rrr(t_data **stk);
void    add_data(t_data *mv, t_data *on);
void	init(t_data **stk, t_data *n, int val, int *err);
void	show_all(t_data **stk, int n);
void	show_a(t_data **stk);
void	show_b(t_data **stk);
void	process(t_data **stk);
t_data	**mem_stack(int n);
int		main(int narg, char **args);
/*___Bonus part___*/
#endif
