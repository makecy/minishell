/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psostari <psostari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 10:37:41 by psostari          #+#    #+#             */
/*   Updated: 2024/10/24 10:48:23 by psostari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_tokens(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		printf("Token: %s, Type: %d\n", current->value, current->type);
		current = current->next;
	}
}

int	main(void)
{
	char	*input;
	t_token	*tokens;

	input = "ls -l | grep 'test' >> output.txt && echo 'done'";
	tokens = tokenize_input(input);
	if (tokens == NULL)
	{
		printf("No tokens found.\n");
		return (1);
	}
	print_tokens(tokens);
	ft_clear_token_list(&tokens);
	return (0);
}
