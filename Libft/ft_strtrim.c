/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:06:59 by mstefano          #+#    #+#             */
/*   Updated: 2023/10/23 15:16:12 by mstefano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*newstr;
	size_t	len;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (set[i] == '\0' || s1[i] == '\0')
		return (ft_strdup(s1));
	len = ft_strlen(s1);
	while (ft_strchr(set, s1[i]))
		i++;
	while (ft_strrchr(set, s1[len - j - 1]))
		j++;
	newstr = ft_substr(s1, i, len - i - j);
	return (newstr);
}
