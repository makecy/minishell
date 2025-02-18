/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 18:35:53 by mstefano          #+#    #+#             */
/*   Updated: 2024/12/23 20:01:32 by mstefano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	apply_input_redirection(t_redirection *redir)
{
	int	fd;

	if (ft_strcmp(redir->type, "<<") == 0)
		handle_heredoc(redir->file);
	else if (ft_strcmp(redir->type, "<") == 0)
	{
		fd = open(redir->file, O_RDONLY);
		if (fd == -1)
			exit(EXIT_FAILURE);
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			close(fd);
			exit(EXIT_FAILURE);
		}
		close(fd);
	}
	else
		exit(EXIT_FAILURE);
}

void	handle_heredoc(const char *delimiter)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
	{
		perror("Failed to create pipe for heredoc");
		exit(EXIT_FAILURE);
	}
	read_heredoc_lines(pipefd, delimiter);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		perror("Failed to redirect input for heredoc");
		close(pipefd[0]);
		exit(EXIT_FAILURE);
	}
	close(pipefd[0]);
}

void	apply_output_redirection(t_redirection *redir)
{
	int	fd;

	if (ft_strcmp(redir->type, ">>") == 0)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (ft_strcmp(redir->type, ">") == 0)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
	{
		fprintf(stderr, "Invalid output redirection type: %s\n", redir->type);
		exit(EXIT_FAILURE);
	}
	if (fd == -1)
	{
		perror("Failed to open file for output redirection");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("Failed to redirect output");
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
}

int	handle_redirections(t_command *command)
{
	t_redirection	*redir;
	int				redirect_count;

	redirect_count = 0;
	if (!command)
		return (-1);
	redir = command->redirections;
	while (redir)
	{
		if (ft_strcmp(redir->type, "<") == 0 || ft_strcmp(redir->type,
				"<<") == 0)
			apply_input_redirection(redir);
		else if (ft_strcmp(redir->type, ">") == 0 || ft_strcmp(redir->type,
				">>") == 0)
			apply_output_redirection(redir);
		else
			return (-1);
		redir = redir->next;
	}
	return (0);
}

void	parse_redirections(char **tokens, t_command *command)
{
	size_t	i;
	size_t	j;
	size_t	arg_count;
	char	**new_args;

	count_arguments(tokens, &arg_count);
	new_args = allocate_new_args(arg_count);
	if (!new_args)
		return ;
	i = 0;
	j = 0;
	while (tokens[i])
	{
		if (is_redirection_token(tokens[i]))
		{
			if (!handle_redirection_token(tokens, &i, command, new_args))
				return ;
		}
		else
			new_args[j++] = ft_strdup(tokens[i++]);
	}
	new_args[j] = NULL;
	command->args = new_args;
}
