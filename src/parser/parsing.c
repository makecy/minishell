/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:06:21 by mstefano          #+#    #+#             */
/*   Updated: 2024/12/23 19:37:15 by mstefano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*read_input(void)
{
	char	*input;

	input = readline("minishell$ ");
	if (input && *input)
		add_history(input);
	return (input);
}

void	parse_tokens_recursive(char **tokens, int index)
{
	if (tokens[index] == NULL)
		return ;
	printf("Token[%d]: %s\n", index, tokens[index]);
	parse_tokens_recursive(tokens, index + 1);
}

void	parse_tokens(char **tokens)
{
	if (tokens[0] == NULL)
		return ;
	parse_tokens_recursive(tokens, 0);
}

char	**append_arg(char **args, char *new_arg)
{
	int		i;
	char	**new_args;
	int		j;

	if (!args)
		return (create_initial_args(new_arg));
	i = 0;
	while (args[i])
		i++;
	new_args = malloc((i + 2) * sizeof(char *));
	if (!new_args)
	{
		perror("malloc failed");
		return (NULL);
	}
	j = 0;
	while (j < i)
	{
		new_args[j] = args[j];
		j++;
	}
	new_args[i] = strdup(new_arg);
	new_args[i + 1] = NULL;
	free(args);
	return (new_args);
}

t_command	*parse_commands(char **tokens)
{
	t_command	*head;
	t_command	*current;
	int			i;

	head = NULL;
	current = NULL;
	i = 0;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], "|") == 0)
		{
			handle_pipe_token(&current);
			i++;
			continue ;
		}
		if (!current)
		{
			current = create_new_command();
			head = current;
		}
		current->args = append_arg(current->args, tokens[i]);
		i++;
	}
	parse_redirections_for_commands(head);
	return (head);
}
