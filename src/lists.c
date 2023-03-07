/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsusanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:50:59 by fsusanna          #+#    #+#             */
/*   Updated: 2023/03/07 15:31:34 by fsusanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

typedef struct s_list
{
	int				datum;
	int				initial;
	int				target;
	struct s_list	**base;
	struct s_list	*prev;
	struct s_list	*next;
}			t_list;
t_list	*ft_lstnew(int *data, int pos);

void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

t_list	*ft_lstnew(int *data, int pos)
{
	t_list	*ret;

	ret = malloc(sizeof(*ret));
	if (!ret)
		return (NULL);
	ret->datum = data[pos];
	ret->initial = pos;
	ret->target = -1;
	ret->base = malloc(sizeof(*(ret->base)));
	if (!(ret->base))
	{
		free(ret);
		return (NULL);
	}
	*(ret->base) = ret;
	ret->prev = ret;
	ret->next = ret;
	return (ret);
}
