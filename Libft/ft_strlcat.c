/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:09:43 by mstefano          #+#    #+#             */
/*   Updated: 2023/10/24 17:00:28 by mstefano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	total;

	i = 0;
	j = 0;
	while (i < dstsize && (dst[i]))
		i++;
	if (dstsize == 0)
		return (i + ft_strlen(src));
	while (i + j < dstsize - 1 && src[j])
	{
		dst[i + j] = src[j];
		j++;
	}
	if (dstsize > i)
		dst[j + i] = '\0';
	total = i + j;
	while (src[j])
	{
		total++;
		j++;
	}
	return (total);
}
