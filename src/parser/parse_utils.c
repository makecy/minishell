/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 19:19:50 by mstefano          #+#    #+#             */
/*   Updated: 2024/12/23 19:36:07 by mstefano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**create_initial_args(char *new_arg)
{
	char	**new_args;

	new_args = malloc(2 * sizeof(char *));
	if (!new_args)
	{
		perror("malloc failed");
		return (NULL);
	}
	new_args[0] = strdup(new_arg);
	new_args[1] = NULL;
	return (new_args);
}

t_command	*create_new_command(void)
{
	t_command	*new_command;

	new_command = malloc(sizeof(t_command));
	if (!new_command)
	{
		perror("malloc failed");
		return (NULL);
	}
	new_command->args = NULL;
	new_command->redirections = NULL;
	new_command->next = NULL;
	return (new_command);
}

void	handle_pipe_token(t_command **current)
{
	(*current)->next = create_new_command();
	*current = (*current)->next;
}

void	parse_redirections_for_commands(t_command *head)
{
	t_command	*temp;

	temp = head;
	while (temp)
	{
		parse_redirections(temp->args, temp);
		temp = temp->next;
	}
}
