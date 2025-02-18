/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 09:10:30 by psostari          #+#    #+#             */
/*   Updated: 2024/12/23 20:25:18 by mstefano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	quote_span(const char *str)
{
	int		span;
	char	s;

	s = *str;
	span = 1;
	if (str == NULL || *str == '\0')
		return (0);
	while (str[span] && str[span] != s)
		++span;
	if (str[span] == '\0')
		span--;
	return (span);
}

int	token_len(const char *str)
{
	int	len;

	len = 0;
	if (check_if_redirection(*str) && *str == *(str + 1))
		return (2);
	if (check_if_operator(*str))
		return (1);
	while (*(str + len) && !is_special_char(*(str + len)))
	{
		if (check_if_quote(*(str + len)))
			len += quote_span(str + len);
		++len;
	}
	return (len);
}

char	*take_token(const char *str, int *i)
{
	char	*token_str;
	int		len;

	while (is_spaceortab(str[*i]))
		*i += 1;
	len = token_len(str + *i);
	token_str = (char *)malloc(sizeof(char) * len + 1);
	ft_strlcpy(token_str, str + *i, len + 1);
	*i += len;
	return (token_str);
}

static char	*get_token(const char *input, int *i, int *err)
{
	int	start;

	if (!input[*i])
		return (NULL);
	if (input[*i] == '\"' || input[*i] == '\'')
		return (parse_quoted_token(input, i, err));
	if (input[*i] == '>' && input[*i + 1] == '>')
	{
		*i += 2;
		return (strndup(">>", 2));
	}
	if (input[*i] == '<' || input[*i] == '>' || input[*i] == '|')
		return (strndup(&input[(*i)++], 1));
	start = *i;
	while (input[*i] && input[*i] != ' ' && input[*i] != '\t'
		&& !is_special_char(input[*i]))
		(*i)++;
	if (*i > start)
		return (strndup(input + start, *i - start));
	return (NULL);
}

char	**tokenize_input(const char *input_line, int i, int err)
{
	char	**tokens;
	int		token_index;
	char	*token;

	tokens = malloc(sizeof(char *) * MAX_TOKENS);
	if (!tokens)
		return (NULL);
	token_index = 0;
	while (input_line[i])
	{
		while (input_line[i] == ' ' || input_line[i] == '\t')
			i++;
		if (!input_line[i])
			break ;
		token = get_token(input_line, &i, &err);
		if (err)
		{
			free_tokens_on_error(tokens, token_index);
			return (NULL);
		}
		if (token)
			tokens[token_index++] = token;
	}
	return (tokens[token_index] = NULL, tokens);
}
