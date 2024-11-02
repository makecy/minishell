/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:24:01 by mstefano          #+#    #+#             */
/*   Updated: 2024/10/28 18:01:03 by mstefano         ###   ########.fr       */
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
	pid = fork();;
	
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