/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 10:37:41 by psostari          #+#    #+#             */
/*   Updated: 2024/11/02 21:31:10 by mstefano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main ()
{
	char *input;
	char **tokens;

	while (1)
	{
		input = read_input();
		if (!input)
			break ;
			tokens = tokenize_input(input);
		if (tokens[0] != NULL)
		execute_command(tokens);
	}
	free(input);
	free(tokens);
}
