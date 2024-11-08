/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:41:43 by psostari          #+#    #+#             */
/*   Updated: 2024/11/08 13:39:11 by mstefano         ###   ########.fr       */
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

char **tokenize_input(char *input)
{
	char	**tokens;
	char	quote;
	int		token_index;
	int		start;
	int		i;
	tokens = malloc(sizeof(char *) * (MAX_TOKENS));
	token_index = 0;
	i = 0;

	while (input[i] != '\0')
	{
		while (input[i] == ' ' || input[i] == '\t')
			i++;
		if (input[i] == '\"' || input[i] == '\'')
		{
			quote = input[i++];
			start = i;
			while (input[i] != '\0' && input[i] != quote)
				i++;
			if (input[i] == '\0')
			{
				fprintf(stderr, "Error: unmatched quote\n");
				free(tokens);
				return NULL;
			}
			tokens[token_index++] = ft_strndup(&input[start], i - start);
			i++;
		}
		else if (is_special_char(input[i]))
		{
			tokens[token_index++] = ft_strndup(&input[i], 1);
			i++;
		}
		else
		{
			int start = i;
			while (input[i] != '\0' && input[i] != ' ' && input[i] != '\t' && !is_special_char(input[i]))
				i++;
			tokens[token_index++] = ft_strndup(&input[start], i - start);
		}
	}

	tokens[token_index] = NULL;
	return tokens;
}
