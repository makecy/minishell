/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psostari <psostari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:41:43 by psostari          #+#    #+#             */
/*   Updated: 2024/10/24 12:09:36 by psostari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Function to calculate the distance(span) to the closing quote (form " to ")
int span -> var that traks the number of char beteen " and ".
char s -> var that stores first char of str (treated as opening quote ")
*/
/*parent of f4d1c79... added parsing, now when you ./minishell
 you go into a so called shell*/
int	quote_span(const char *str)
{
	int		span;
	char	s;

	s = *str;
	span = 1;
	if (str == NULL || *str == '\0')
		return (0);
	while (str[span] && str[span] != s)
	{
		++span;
	}
	if (str[span] == '\0')
		span--;
	return (span);
}

/*function caculates the len of the tokens which consist
of different char within the str*/
/*parent of f4d1c79... added parsing, now when you ./minishell
 you go into a so called shell*/
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

t_token	*take_token(const char *str, int *i)
{
	char			*token_str;
	int				len;
	t_token			*new_token;
	t_token_type	type;

	while (is_spaceortab(str[*i]))
	{
		*i += 1;
	}
	if (check_if_operator(str[*i]))
	{
		if (!strncmp(str + *i, "<<", 2) || !strncmp(str + *i, ">>", 2))
		{
			len = 2;
			type = T_REDIRECTION;
		}
		else if (!strncmp(str + *i, "&&", 2) || !strncmp(str + *i, "||", 2))
		{
			len = 2;
			type = T_AND;
		}
		else
		{
			len = 1;
			type = T_PIPE;
		}
	}
	else
	{
		len = token_len(str + *i);
		type = T_IDENTIFIER;
	}
	token_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!token_str)
	{
		fprintf(stderr, "minishell: allocation error\n");
		exit(EXIT_FAILURE);
	}
	ft_strlcpy(token_str, str + *i, len + 1);
	*i += len;
	new_token = ft_new_token(token_str, type);
	return (new_token);
}

t_token	*tokenize_input(char *input)
{
	t_token	*tokens;
	t_token	*token;
	int		i;

	i = 0;
	tokens = NULL;
	while (input[i])
	{
		token = take_token(input, &i);
		if (token)
		{
			ft_token_list_add_back(&tokens, token);
		}
	}
	return (tokens);
}
