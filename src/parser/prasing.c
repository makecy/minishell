/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prasing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:06:21 by mstefano          #+#    #+#             */
/*   Updated: 2024/11/02 21:26:19 by mstefano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *read_input(void)
{
	char *input;

	input = readline("minishell$ ");
	if (input && *input)
		add_history(input);
	return (input);
}

void parse_tokens_recursive(char **tokens, int index)
{
	if (tokens[index] == NULL)
		return ;
	printf("Token[%d]: %s\n", index,  tokens[index]);
	parse_tokens_recursive(tokens, index + 1);
}

void parse_tokens(char **tokens)
{
	if (tokens[0] == NULL)
		return ;
	parse_tokens_recursive(tokens, 0);
}