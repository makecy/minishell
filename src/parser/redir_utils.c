/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 19:38:54 by mstefano          #+#    #+#             */
/*   Updated: 2024/12/23 20:01:23 by mstefano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_redirection_token(const char *token)
{
	return (ft_strcmp(token, ">") == 0 || ft_strcmp(token, ">>") == 0
		|| ft_strcmp(token, "<") == 0 || ft_strcmp(token, "<<") == 0);
}

void	count_arguments(char **tokens, size_t *arg_count)
{
	size_t	i;

	i = 0;
	*arg_count = 0;
	while (tokens[i])
	{
		if (!is_redirection_token(tokens[i]))
		{
			(*arg_count)++;
			i++;
		}
		else
			i += 2;
	}
}

char	**allocate_new_args(size_t arg_count)
{
	char	**new_args;

	new_args = malloc(sizeof(char *) * (arg_count + 1));
	if (!new_args)
		return (NULL);
	return (new_args);
}

int	handle_redirection_token(char **tokens, size_t *i, t_command *command,
		char **new_args)
{
	t_redirection	*redir;

	if (!tokens[*i + 1])
	{
		free(new_args);
		return (0);
	}
	redir = malloc(sizeof(t_redirection));
	if (!redir)
	{
		free(new_args);
		return (0);
	}
	redir->type = ft_strdup(tokens[*i]);
	redir->file = ft_strdup(tokens[*i + 1]);
	redir->next = command->redirections;
	command->redirections = redir;
	*i += 2;
	return (1);
}

void	read_heredoc_lines(int pipefd[2], const char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			fprintf(stderr, "Warning: EOF received (wanted '%s')\n", delimiter);
			break ;
		}
		if (strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(pipefd[1], line, strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);
}
