/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 21:02:05 by mstefano          #+#    #+#             */
/*   Updated: 2023/10/31 17:26:37 by mstefano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*current;
	void	*temp;

	new = NULL;
	while (lst)
	{
		if (f)
			temp = (f(lst->content));
		if (!temp)
			ft_lstclear(&new, del);
		current = ft_lstnew(temp);
		if (!current)
		{
			ft_lstclear(&new, del);
			del(temp);
		}
		ft_lstadd_back(&new, current);
		lst = lst->next;
	}
	return (new);
}
