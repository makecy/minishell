/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:24:01 by mstefano          #+#    #+#             */
/*   Updated: 2024/12/23 20:29:55 by mstefano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	wait_for_child(pid_t pid)
{
	int	status;

	if (waitpid(pid, &status, WUNTRACED) == -1)
	{
		perror("minishell");
		return ;
	}
	if (!WIFEXITED(status) && !WIFSIGNALED(status))
		wait_for_child(pid);
}

void	execute_command(t_command *command)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (handle_redirections(command) != 0)
		{
			fprintf(stderr, "Redirection failed\n");
			exit(EXIT_FAILURE);
		}
		if (ft_is_builtin(command->args[0]))
			execute_builtin(command->args, command);
		else
			exec_external_command(command->args, environ, -1);
		exit(EXIT_SUCCESS);
	}
	else if (pid > 0)
		wait(NULL);
	else
	{
		perror("fork failed");
		exit(EXIT_FAILURE);
	}
}

static void	setup_builtin_redirection(t_command *command,
										int *fd, int *stdout_copy)
{
	t_redirection	*redir;

	if (!command || !command->redirections)
		return ;
	redir = command->redirections;
	while (redir)
	{
		if (ft_strcmp(redir->type, ">") == 0)
		{
			*fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (*fd < 0)
			{
				perror("open failed");
				return ;
			}
			*stdout_copy = dup(STDOUT_FILENO);
			dup2(*fd, STDOUT_FILENO);
			close(*fd);
		}
		redir = redir->next;
	}
}

void	execute_builtin(char **tokens, t_command *command)
{
	int	fd;
	int	stdout_copy;

	fd = -1;
	stdout_copy = -1;
	setup_builtin_redirection(command, &fd, &stdout_copy);
	if (ft_strcmp(tokens[0], "echo") == 0)
		ft_echo(tokens);
	else if (ft_strcmp(tokens[0], "cd") == 0)
		ft_cd(tokens[1]);
	else if (ft_strcmp(tokens[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(tokens[0], "env") == 0)
		ft_env();
	else if (ft_strcmp(tokens[0], "exit") == 0)
		ft_exit(tokens);
	if (stdout_copy != -1)
	{
		dup2(stdout_copy, STDOUT_FILENO);
		close(stdout_copy);
	}
}

void	exec_external_command(char **tokens, char **envp, int i)
{
	char	*path_env;
	char	**paths;
	char	full_path[1024];

	path_env = getenv("PATH");
	if (!path_env)
	{
		printf("PATH not found.\n");
		return ;
	}
	paths = ft_split(path_env, ':');
	while (paths[++i])
	{
		ft_strcpy(full_path, paths[i]);
		ft_strcat(full_path, "/");
		ft_strcat(full_path, tokens[0]);
		if (access(full_path, X_OK) == 0)
		{
			execve(full_path, tokens, envp);
			perror("Execve failed");
			exit(EXIT_FAILURE);
		}
	}
	printf("minishell: command not found: %s\n", tokens[0]);
	exit(EXIT_FAILURE);
}
