/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:28:38 by psostari          #+#    #+#             */
/*   Updated: 2024/12/22 21:27:44 by mstefano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_find_env_variable(char *name)
{
	t_env_var	*envlst;

	envlst = g_lobal_shell.envlst;
	while (envlst)
	{
		if (!ft_strcmp(name, envlst->name))
			return (true);
		envlst = envlst->next;
	}
	return (false);
}

static t_env_var	*ft_add_env_var(char *name, char *value)
{
	t_env_var	*new;

	new = (t_env_var *)ft_calloc(1, sizeof(t_env_var));
	if (!new)
		return (NULL);
	new->name = ft_memory_box(ft_strdup(name), false);
	if (value)
		new->value = ft_memory_box(ft_strdup(value), false);
	new->next = NULL;
	return (new);
}

char	*ft_get_envlst_val(char *name)
{
	t_env_var	*envlst;

	envlst = g_lobal_shell.envlst;
	while (envlst)
	{
		if (!ft_strcmp(name, envlst->name))
			return (envlst->value);
		envlst = envlst->next;
	}
	return (NULL);
}

void	ft_env_var_to_end(t_env_var *new)
{
	t_env_var	*curr;

	if (!g_lobal_shell.envlst)
	{
		g_lobal_shell.envlst = new;
		return ;
	}
	curr = g_lobal_shell.envlst;
	while (curr && curr->next)
		curr = curr->next;
	curr->next = new;
}

void	set_environment_variable(char *name, char *value, bool create)
{
	t_env_var	*envlst;
	char		*new_value;

	envlst = g_lobal_shell.envlst;
	while (envlst)
	{
		if (!ft_strcmp(name, envlst->name))
		{
			if (value)
				new_value = ft_strdup(value);
			else
				new_value = NULL;
			free(envlst->value);
			envlst->value = new_value;
			return ;
		}
		envlst = envlst->next;
	}
	if (create)
		ft_env_var_to_end(ft_add_env_var(name, value));
}
