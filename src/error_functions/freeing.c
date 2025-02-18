/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:53:03 by mstefano          #+#    #+#             */
/*   Updated: 2024/12/22 21:30:33 by mstefano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	if (!tokens)
		return ;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

void	free_command(t_command *command)
{
	int	i;

	if (command == NULL)
		return ;
	if (command->args)
	{
		i = 0;
		while (command->args[i])
		{
			free(command->args[i]);
			i++;
		}
		free(command->args);
	}
	free_redirection(command->redirections);
	free(command);
}

void	free_redirection(t_redirection *redir)
{
	t_redirection	*tmp;

	while (redir)
	{
		tmp = redir->next;
		free(redir->file);
		free(redir);
		redir = tmp;
	}
}

void	free_pipeline(t_command *pipeline)
{
	t_command	*tmp;

	while (pipeline)
	{
		tmp = pipeline;
		pipeline = pipeline->next;
		free_command(tmp);
	}
}
