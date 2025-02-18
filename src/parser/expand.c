/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 19:02:11 by mstefano          #+#    #+#             */
/*   Updated: 2024/12/23 18:37:30 by mstefano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*expand_exit_status(char *input, int last_exit_status)
{
	char	*result;
	char	*ptr;
	char	exit_status_str[12];
	int		idx;
	int		i;

	result = malloc(MAX_EXPANSION_SIZE);
	ptr = input;
	idx = 0;
	sprintf(exit_status_str, "%d", last_exit_status);
	while (*ptr)
	{
		if (*ptr == '$' && *(ptr + 1) == '?')
		{
			i = 0;
			while (exit_status_str[i] != '\0')
				result[idx++] = exit_status_str[i++];
			ptr += 2;
		}
		else
			result[idx++] = *ptr++;
	}
	result[idx] = '\0';
	return (result);
}

static void	expand_single_variable(char **input,
									char *result, int *res_len, char **envp)
{
	char	key[MAX_VAR_LENGTH];
	int		i;
	char	*value;

	i = 0;
	(*input)++;
	while (ft_isalnum(**input) || **input == '_')
		key[i++] = *((*input)++);
	key[i] = '\0';
	value = get_env_value(key, envp);
	if (value)
	{
		ft_strlcat(result, value, MAX_EXPANSION_SIZE);
		*res_len += ft_strlen(value);
		free(value);
	}
}

char	*expand_env_variables(char *input, char **envp)
{
	char	*result;
	int		res_len;

	result = ft_calloc(MAX_EXPANSION_SIZE, sizeof(char));
	res_len = 0;
	while (*input)
	{
		if (*input == '$' && *(input + 1) && (ft_isalnum(*(input + 1))
				|| *(input + 1) == '_'))
			expand_single_variable(&input, result, &res_len, envp);
		else
		{
			result[res_len++] = *input++;
			result[res_len] = '\0';
		}
	}
	return (result);
}

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
	return (NULL);
}
