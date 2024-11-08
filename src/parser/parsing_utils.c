/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:32:53 by mstefano          #+#    #+#             */
/*   Updated: 2024/11/08 13:34:13 by mstefano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *ft_strndup(const char *src, size_t n)
{
	char *dup;
	size_t len;

	len = ft_strlen(src);
	if (n < len)
		len = n;
	dup = malloc(len + 1);
	if (!dup)
		return NULL;
	ft_memcpy(dup, src, len);
	dup[len] = '\0';
	return dup;
}
