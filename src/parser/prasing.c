/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prasing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:06:21 by mstefano          #+#    #+#             */
/*   Updated: 2024/11/08 16:17:56 by mstefano         ###   ########.fr       */
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
		return;
	printf("Token[%d]: %s\n", index, tokens[index]);
	parse_tokens_recursive(tokens, index + 1);
}

void parse_tokens(char **tokens)
{
	if (tokens[0] == NULL)
		return;
	parse_tokens_recursive(tokens, 0);
}

void parse_redirections(char **tokens, t_command *command)
{
	int i;

	i = 0;
	while (tokens[i])
	{
		if (ft_strncmp(tokens[i], ">", 1) == 0 || ft_strncmp(tokens[i], ">>", 2) == 0 ||
			ft_strncmp(tokens[i], "<", 1) == 0 || ft_strncmp(tokens[i], "<<", 2) == 0)
		{
			t_redirection *redir = malloc(sizeof(t_redirection));
			redir->type = ft_strdup(tokens[i]);
			redir->file = ft_strdup(tokens[++i]);
			redir->next = command->redirections;
			command->redirections = redir;
			i++;
		}
	}
}

t_command *parse_commands(char **tokens)
{
	t_command *head;
	t_command *current;
	int i;

	i = 0;
	current = NULL;
	head = NULL;
	while (tokens[i])
	{
		if (ft_strncmp(tokens[i], "|", 1) == 0)
		{
			if (current)
			{
				current->next = malloc(sizeof(t_command));
				current = current->next;
			}
		}
		else
		{
			if (!current)
			{
				head = malloc(sizeof(t_command));
				current = head;
			}
			current->args = append_arg(current->args, tokens[i]);
		}
		i++;
	}
	return head;
}

char *expand_env_vars(char *input)
{
	char *expanded;
	char var_name[MAX_VAR_LENGTH];
	char *var_value = NULL;
	int i;
	int j;
	int k;

	expanded = malloc(MAX_EXPANSION_SIZE);
	i = 0;
	j = 0;

	while (input[i] != '\0')
	{
		if (input[i] == '$' && is_valid_var_char(input[i + 1], 1))
		{
			k = 0;
			i++;
			while (is_valid_var_char(input[i], 0))
			{
				var_name[k++] = input[i++];
			}
			var_name[k] = '\0';
			var_value = getenv(var_name);
			if (var_value)
			{
				j += snprintf(&expanded[j], MAX_EXPANSION_SIZE - j, "%s", var_value);
			}
		}
		else
		{
			expanded[j++] = input[i++];
		}
	}
	expanded[j] = '\0';
	return expanded;
}

