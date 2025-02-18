/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 09:20:54 by psostari          #+#    #+#             */
/*   Updated: 2024/12/22 21:27:04 by mstefano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_remove_env_var(t_env_var **head, const char *name)
{
	t_env_var	*current;
	t_env_var	*prev;

	if (!head || !*head || !name)
		return ;
	current = *head;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*head = current->next;
			free(current->name);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

static int	is_valid_identifier(char *arg)
{
	int	i;

	if (!arg || !ft_isalpha(arg[0]))
		return (0);
	i = 0;
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	ft_unset(char **args)
{
	int	i;
	int	exit_status;

	exit_status = 0;
	if (!args[1])
		return (0);
	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			exit_status = 1;
		}
		else
			ft_remove_env_var(&g_lobal_shell.envlst, args[i]);
		i++;
	}
	return (exit_status);
}
