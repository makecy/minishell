/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psostari <psostari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 19:33:06 by mstefano          #+#    #+#             */
/*   Updated: 2024/10/23 09:17:36 by psostari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main ()
{
	char	*input;
	char	**tokens;

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
