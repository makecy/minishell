/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:31:36 by mstefano          #+#    #+#             */
/*   Updated: 2023/10/17 14:49:16 by mstefano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*a;
	size_t	len;
	size_t	i;

	a = (char *)s1;
	len = ft_strlen(s1);
	a = malloc(len * sizeof(char) + 1);
	if (!a)
	{
		return (NULL);
	}
	i = 0;
	while (len > i)
	{
		a[i] = s1[i];
		i++;
	}
	a[i] = '\0';
	return (a);
}
