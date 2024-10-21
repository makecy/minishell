/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:21:45 by mstefano          #+#    #+#             */
/*   Updated: 2023/10/23 16:30:03 by mstefano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const char	*s;
	char		*d;

	if (n == 0 || (dst == NULL && src == NULL))
		return (dst);
	d = (char *)dst;
	s = (const char *)src;
	while (n--)
	{
		*d++ = *s++;
	}
	return (dst);
}
