/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 09:46:01 by psostari          #+#    #+#             */
/*   Updated: 2024/12/22 21:24:26 by mstefano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	export_err(char *name)
{
	write(2, "export: `", 9);
	write(2, name, strlen(name));
	write(2, "': not a valid identifier\n", 26);
	free(name);
	return (1);
}

int	name_check(const char *name)
{
	if (!name || (!ft_isalpha(*name) && *name != '_'))
		return (0);
	name++;
	while (*name && *name != '=')
	{
		if (!ft_isalnum(*name) && *name != '_')
			return (0);
		name++;
	}
	return (1);
}

void	export_var(const char *name, const char *value)
{
	t_env_var	*tmp;

	tmp = g_lobal_shell.envlst;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
		{
			update_existing_var(tmp, value);
			return ;
		}
		tmp = tmp->next;
	}
	add_new_var(name, value);
}

void	parse_name_value(const char *arg, char **name, char **value)
{
	char	*equals;
	size_t	name_len;

	equals = ft_strchr(arg, '=');
	if (!equals)
	{
		*name = ft_strdup(arg);
		*value = NULL;
		return ;
	}
	name_len = equals - arg;
	*name = ft_substr(arg, 0, name_len);
	*value = ft_strdup(equals + 1);
}

void	process_export_arg(char *name, char *value, int *exit_status)
{
	if (!name_check(name))
	{
		*exit_status = export_err(name);
		if (value != NULL)
			free(value);
	}
	else
	{
		if (value == NULL)
			export_var(name, "");
		else
			export_var(name, value);
	}
}
