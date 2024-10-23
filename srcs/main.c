/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 19:33:06 by mstefano          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/10/23 19:41:36 by mstefano         ###   ########.fr       */
=======
/*   Updated: 2024/10/21 13:30:31 by mstefano         ###   ########.fr       */
>>>>>>> parent of f4d1c79... added parsing, now when you ./minishell you go into a so called shell
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main (int ac, char **av)
{
<<<<<<< HEAD
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
=======
	(void) ac ;
	(void) av ;
	return (0);
}
>>>>>>> parent of f4d1c79... added parsing, now when you ./minishell you go into a so called shell
