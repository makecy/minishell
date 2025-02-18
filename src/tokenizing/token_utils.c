/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 10:03:19 by psostari          #+#    #+#             */
/*   Updated: 2024/12/23 18:50:13 by mstefano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_if_operator(int c)
{
	return (c == '&' || c == '|');
}

t_token	*ft_new_token(char *value, t_token_type type)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = value;
	new_token->type = type;
	new_token->next = NULL;
	return (new_token);
}

void	ft_token_list_add_back(t_token **lst, t_token *new_token)
{
	t_token	*curr_node;

	if (!*lst)
	{
		*lst = new_token;
		return ;
	}
	curr_node = *lst;
	while (curr_node->next)
		curr_node = curr_node->next;
	curr_node->next = new_token;
}

void	ft_clear_token_list(t_token **lst)
{
	t_token	*curr_node;
	t_token	*next;

	curr_node = *lst;
	while (curr_node)
	{
		free(curr_node->value);
		next = curr_node->next;
		free(curr_node);
		curr_node = next;
	}
	*lst = NULL;
}

char	*parse_quoted_token(const char *input, int *i, int *error_flag)
{
	char	quote;
	int		start;
	char	*token;

	quote = input[*i];
	(*i)++;
	start = *i;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (!input[*i])
	{
		*error_flag = 1;
		return (NULL);
	}
	token = strndup(input + start, *i - start);
	(*i)++;
	return (token);
}
