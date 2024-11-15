/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:24:01 by mstefano          #+#    #+#             */
/*   Updated: 2024/11/15 17:24:25 by mstefano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void wait_for_child(pid_t pid)
{
	int status;
	
	if (waitpid(pid, &status, WUNTRACED) == -1)
	{
		perror("minishell");
		return ;
	}
	if (!WIFEXITED(status) && !WIFSIGNALED(status))
		wait_for_child(pid);
}

void execute_command(char **tokens)
{
	pid_t pid;
	
	pid = fork();
	if (is_builtin(tokens[0]))
	{
		execute_builtin(tokens);
		return ;
	}
	if (pid == 0)
	{
		if (execve(tokens[0], tokens, NULL) == -1)
			perror("minishell");
		exit(EXIT_FAILURE);
	}
		else if (pid < 0)
			perror("minishell");
		else 
			wait_for_child(pid);
}

int	is_builtin(char *command)
{
    return (ft_strncmp(command, "cd", 2) == 0 || ft_strncmp(command, "echo", 4) == 0 ||
            ft_strncmp(command, "exit", 4) == 0 || ft_strncmp(command, "env", 4) == 0);
}

void	execute_builtin(char **tokens)
{
	int	i;

	if (ft_strncmp(tokens[0], "cd", 2) == 0)
	{
		if (tokens[1] != NULL)
		{
			if (chdir(tokens[1]) != 0)
				perror("cd");
		}
	else
		fprintf(stderr, "cd: expected argument \n");
	}
	else if (ft_strncmp(tokens[0], "echo", 4) == 0)
	{
		i = 0;
		while (tokens[i] != NULL)
		{
			printf("%s", tokens[i]);
			i++;
		}
		printf("\n");
		
	}
	else if (ft_strncmp(tokens[0], "exit", 4) == 0)
		exit(0);
}