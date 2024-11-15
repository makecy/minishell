/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:05:43 by mstefano          #+#    #+#             */
/*   Updated: 2024/11/15 15:25:07 by mstefano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_value(const char *key, char **envp)
{
	size_t	key_len;
	int		i;
	
	key_len = ft_strlen(key);
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], key, key_len) == 0 && envp[i][key_len] == '=')
			return (ft_strdup(&envp[i][key_len + 1]));
		i++;
	}
	return NULL;
}

char	*expand_env_variables(char *input, char **envp)
{
	char	*result;
	char	*ptr;
	char	*value;
	char	key[MAX_VAR_LENGTH];
	int		i;
	
	result = ft_calloc(MAX_EXPANSION_SIZE, sizeof(char));
	result[0] = '\0';
	ptr = input;
	while (*ptr)
	{
		if (*ptr == '$' && (*(ptr + 1) != '\0' && (ft_isalnum(*(ptr + 1)) || *(ptr + 1) == '_')))
		{
			ptr++;
			i = 0;
			while (ft_isalnum(*ptr) || (*ptr == '_'))
				key[i++] = *ptr++;
			key[i] = '\0';
			value = get_env_value(key, envp);
			if (value)
			{
				ft_strlcat(result, value, MAX_EXPANSION_SIZE);
				free(value);
			}
		}
		else
		{	
			ft_strlcat(result, ptr, MAX_EXPANSION_SIZE);
			ptr++;
		}
	}
	return (result);
}
