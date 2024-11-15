/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:06:21 by mstefano          #+#    #+#             */
/*   Updated: 2024/11/15 16:56:14 by mstefano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*read_input_n_expand_env(char **envp)
{
	char	*input;
	char	*expanded_input;

	expanded_input = NULL;
	input = readline("minishell > ");
	if (input && *input)
	{
		add_history(input);
		expanded_input = expand_env_variables(input, envp);
		free(input);
	}
	return (expanded_input);
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

void	parse_redirections(char **tokens, t_command *command)
{
	int				i;
	t_redirection	*redir;

	i = 0;
	while (tokens[i])
	{
		if (ft_strncmp(tokens[i], ">", 1) == 0
			|| ft_strncmp(tokens[i], ">>", 2) == 0
			|| ft_strncmp(tokens[i], "<", 1) == 0
			|| ft_strncmp(tokens[i], "<<", 2) == 0)
		{
			redir = malloc(sizeof(t_redirection));
			redir->type = ft_strdup(tokens[i]);
			redir->file = ft_strdup(tokens[++i]);
			redir->next = command->redirections;
			command->redirections = redir;
			i++;
		}
	}
}

t_command	*parse_commands(char **tokens)
{
	t_command	*head;
	t_command	*current;
	int			i;

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
	return (head);
}

// char	*expand_env_vars(char *input)
// {
// 	char	*expanded;
// 	char	var_name[MAX_VAR_LENGTH];
// 	char	*var_value;
// 	int		indices[3]; // previously int i, j, k now indices[0] = i, indices[1] = j, indices[2] = k
	
// 	expanded = malloc(MAX_EXPANSION_SIZE);
// 	var_value = NULL;
// 	indices[0] = 0;
// 	indices[1] = 0;
// 	while (input[indices[0]] != '\0')
// 	{
// 		if (input[indices[0]] == '$'
// 			&& is_valid_var_char(input[indices[0] + 1], 1))
// 		{
// 			indices[2] = 0;
// 			indices[0]++;
// 			while (is_valid_var_char(input[indices[0]], 0))
// 				var_name[indices[2]++] = input[indices[0]++];
// 			var_name[indices[2]] = '\0';
// 			var_value = getenv(var_name);
// 			if (var_value)
// 				indices[1] += snprintf(&expanded[indices[1]], MAX_EXPANSION_SIZE - indices[1], "%s", var_value);
// 		}
// 		else
// 			expanded[indices[1]++] = input[indices[0]++];
// 	}
// 	expanded[indices[1]] = '\0'; return expanded;
// }
