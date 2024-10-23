/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psostari <psostari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 09:45:50 by psostari          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/10/23 19:44:05 by mstefano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


=======
/*   Updated: 2024/10/22 11:33:31 by psostari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Function to calculate the distance(span) to the closing quote (form " to ")
int span -> var that traks the number of char beteen " and ".
char s -> var that stores first char of str (treated as opening quote ")
*/
>>>>>>> parent of f4d1c79... added parsing, now when you ./minishell you go into a so called shell
static int	quote_span(const char *str)
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

<<<<<<< HEAD

=======
/*function caculates the len of the tokens which consist
of different char within the str*/
>>>>>>> parent of f4d1c79... added parsing, now when you ./minishell you go into a so called shell
static int	token_len(const char *str)
{
	int	len;

	len = 0;
	if (check_if_redirection(*str) && *str == *(str + 1))
		return (2);
	if (check_if_operator(*str))
		return (1);
	while (*(str + len) && !is_special_char(*(str + len)))
	{
		if (is_quotechr(*(str + len)))
			len += quote_span(str + len);
		++len;
	}
	return (len);
}

<<<<<<< HEAD
char	*take_token(const char *str, int *i)s
=======
/* skips the spaces, increments the index as long it is white space,
calculate len of token, allocation, cpy the token to allocated space and
increments the index by the len of token*/
static char	*take_token(const char *str, int *i)
>>>>>>> parent of f4d1c79... added parsing, now when you ./minishell you go into a so called shell
{
	char			*token_str;
	int				len;
	t_token			*new_token;
	t_token_type	type;

	while (is_spaceortab(str[*i]))
	{
		*i += 1;
	len = token_len(str + *i);
	token_len = (char *)malloc(sizeof(char) * len + 1);
	ft_strcpy(token_str, str + *i, len + 1);
	*i += len;
	return (token_str);
}
<<<<<<< HEAD

char **tokenize_input(char *input)
{
	char	**tokens;
	int i, position, buffsize;
	char *token;

	i = 0;
	position = 0;
	buffsize = BUFFER_SIZE;
	tokens = malloc(buffsize * sizeof(char *));

	if (!tokens)
	{
		fprintf(stderr, "minishell: allocation error\n");
		exit(EXIT_FAILURE);
	}
	while (input[i])
	{
		token = take_token(input, &i);
		if (token)
		{
			tokens[position] = token;
			position++;
			if (position >= buffsize)
			{
				buffsize += BUFFER_SIZE;
				tokens = realloc(tokens, buffsize * sizeof(char *));
				if (!tokens)
				{
					fprintf(stderr, "minishell: allocation error\n");
					exit(EXIT_FAILURE);
				}
			}
		}
		
	}
	tokens[position] = NULL;
	return (tokens);
}
=======
>>>>>>> parent of f4d1c79... added parsing, now when you ./minishell you go into a so called shell
