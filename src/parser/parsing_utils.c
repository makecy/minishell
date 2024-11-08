/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:32:53 by mstefano          #+#    #+#             */
/*   Updated: 2024/11/08 14:21:49 by mstefano         ###   ########.fr       */
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

char	**append_arg(char **args, char *new_arg)
{
    int		i;
	int		j;
	char	**new_args;
	i = 0;

    while (args[i] != NULL) {
        i++;
    }
	new_args = (char **)malloc((i + 2) * sizeof(char *));
    if (!new_args) {
        perror("malloc failed");
        return NULL;
	}
	j = 0;
	while (j < i)
	{
        new_args[j] = args[j];
		j++;
    }
    new_args[i] = new_arg;
    new_args[i + 1] = NULL;
    return new_args;
}

int	is_valid_var_char(char c, int is_first_char)
{
    if (is_first_char) {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
    } else {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_';
    }
}
