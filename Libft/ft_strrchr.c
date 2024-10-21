/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:21:31 by mstefano          #+#    #+#             */
/*   Updated: 2023/10/13 15:13:49 by mstefano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*l;

	l = NULL;
	if (*s == '\0' && (char)c == '\0')
		return ((char *)s);
	while (*s)
	{
		if (*s == (char)c)
			l = (char *)s;
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (l);
}
