/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsusanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:50:59 by fsusanna          #+#    #+#             */
/*   Updated: 2022/07/16 04:13:19 by fsusanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*fcopy;
	t_list	*new;

	fcopy = NULL;
	if (lst && f)
	{
		fcopy = ft_lstnew((*f)((*lst).content));
		lst = (*lst).next;
		while (lst && fcopy)
		{
			new = ft_lstnew((*f)((*lst).content));
			if (!new)
			{
				ft_lstclear(&fcopy, del);
				return (NULL);
			}
			ft_lstadd_back(&fcopy, new);
			lst = (*lst).next;
		}
	}
	return (fcopy);
}
