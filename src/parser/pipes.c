/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 22:37:07 by mstefano          #+#    #+#             */
/*   Updated: 2024/12/23 20:30:08 by mstefano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_child(t_command *current, int input_fd,
							int pipe_fd[2], char **envp)
{
	if (input_fd != STDIN_FILENO)
	{
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}
	if (current->next)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	if (handle_redirections(current) != 0)
	{
		fprintf(stderr, "Redirection failed\n");
		exit(EXIT_FAILURE);
	}
	exec_external_command(current->args, envp, -1);
}

static void	handle_parent(pid_t pid, int *input_fd, int pipe_fd[2],
							t_command **current)
{
	waitpid(pid, NULL, 0);
	if (*input_fd != STDIN_FILENO)
		close(*input_fd);
	if ((*current)->next)
	{
		close(pipe_fd[1]);
		*input_fd = pipe_fd[0];
	}
	*current = (*current)->next;
}

static void	pipeline_step(t_command **current, int *input_fd, char **envp)
{
	int		pipe_fd[2];
	pid_t	pid;

	if ((*current)->next && pipe(pipe_fd) == -1)
	{
		perror("Pipe creation failed");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == 0)
		handle_child(*current, *input_fd, pipe_fd, envp);
	else if (pid > 0)
		handle_parent(pid, input_fd, pipe_fd, current);
	else
	{
		perror("Fork failed");
		exit(EXIT_FAILURE);
	}
}

static void	run_pipeline_loop(t_command *commands, char **envp)
{
	t_command	*current;
	int			input_fd;

	current = commands;
	input_fd = STDIN_FILENO;
	while (current)
		pipeline_step(&current, &input_fd, envp);
	if (input_fd != STDIN_FILENO)
		close(input_fd);
}

void	execute_pipeline(t_command *commands, char **envp)
{
	run_pipeline_loop(commands, envp);
}
