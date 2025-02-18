/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 09:54:21 by psostari          #+#    #+#             */
/*   Updated: 2024/12/22 21:10:46 by mstefano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_retrieve_key(char *str)
{
	size_t	i;

	i = 0;
	if (str == NULL || str[0] == '\0')
		return (NULL);
	while (str[i])
	{
		if (str[i] == '=')
			return (ft_memory_box(ft_substr(str, 0, i), false));
		i++;
	}
	return (ft_strdup(str));
}

char	*ft_retrive_value(char *str)
{
	size_t	i;
	size_t	value_length;
	char	*value_substring;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			i++;
			value_length = ft_strlen(str) - i;
			value_substring = ft_substr(str, i, value_length);
			return (ft_memory_box(value_substring, false));
		}
		i++;
	}
	return (NULL);
}

void	ft_init_envlst(void)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	while (environ[i])
	{
		key = ft_retrieve_key(environ[i]);
		value = ft_retrive_value(environ[i]);
		if (key && value)
			set_environment_variable(key, value, true);
		i++;
	}
}

int	ft_env(void)
{
	t_env_var	*list;

	list = g_lobal_shell.envlst;
	while (list)
	{
		if (list->value != NULL)
			printf("%s=%s\n", list->name, list->value);
		list = list->next;
	}
	return (ENO_SUCCESS);
}
