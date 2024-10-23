/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psostari <psostari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 09:45:50 by psostari          #+#    #+#             */
/*   Updated: 2024/10/23 11:44:25 by psostari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*funtio checks if str have operator(true) if not false*/
int	check_if_operator(const char *str)
{
	if (!strncmp(str, "<<", 2) || !strncmp(str, ">>", 2)
		|| !strncmp(str, "&&", 2) || !strncmp(str, "||", 2)
		|| *str == '|' || *str == '<' || *str == '>')
	{
		return (TRUE);
	}
	return (FALSE);
}

/*
Function to calculate the distance(span) to the closing quote (form " to ")
int span -> var that traks the number of char beteen " and ".
char s -> var that stores first char of str (treated as opening quote ")
*/
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

/* take_token function extracts a token from the input string str
based on the current index i,skips whitespace,
 determines the token type, allocates memory for the token,
 copies the token from the string, and updates the index
 for further processing*/
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
	if (check_if_operator(str + *i))
	{
		// << or >>
		if (!strncmp(str + *i, "<<", 2) || !strncmp(str + *i, ">>", 2))
		{
			len = 2;
			type = T_REDIRECTION;
		}
		// || or &&
		else if (!strncmp(str + *i, "&&", 2) || !strncmp(str + *i, "||", 2))
		{
			len = 2;
			type = T_AND;
		}
		//operator is not one of above
		else
		{
			len = 1;
			type = T_PIPE;
		}
	}
	//if the char is not operator, calls the funtion that cal. the len
	//IDEN.. = comand or variable name(regular identifier)
	else
	{
		len = token_len(str + *i);
		type = T_IDENTIFIER;
	}
	token_str = (char *)malloc(sizeof(char) * (len + 1));
	//if alloacation fails
	if (!token_str)
	{
		fprintf(stderr, "minishell: allocation error\n");
		exit(EXIT_FAILURE);
	}
	//copies substr from str from *i tp token_str till targeted len
	ft_strlcpy(token_str, str + *i, len + 1);
	//update index to cur len
	*i += len;
	new_token = ft_new_token(token_str, type);
	return (new_token);
}

//

t_token	*tokenize_input(char *input)
{
	t_token	*tokens; // variable will hold the linked list of token
	t_token	*token; // variable will temporarily hold each token that is created
	int		i;

	i = 0;
	tokens = NULL;
	while (input[i])
	{
		// Call the take_token function, which retrieves a token from the input string and returns it
		token = take_token(input, &i);
		 // If the token was successfully created, add it to the end of the token list
		if (token)
		{
			ft_token_list_add_back(&tokens, token);
		}
	}
	return (tokens);
}
