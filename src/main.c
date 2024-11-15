/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 10:37:41 by psostari          #+#    #+#             */
/*   Updated: 2024/11/15 16:53:38 by mstefano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main (int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	char *input;
	char **tokens;

	while (1)
	{
		input = read_input_n_expand_env(envp);
		if (!input)
			break ;
			tokens = tokenize_input(input);
		if (tokens[0] != NULL)
		execute_command(tokens);
	}
	free(input);
	free(tokens);
}
