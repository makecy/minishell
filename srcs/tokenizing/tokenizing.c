/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psostari <psostari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 09:45:50 by psostari          #+#    #+#             */
/*   Updated: 2024/10/22 11:33:31 by psostari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Function to calculate the distance(span) to the closing quote (form " to ")
int span -> var that traks the number of char beteen " and ".
char s -> var that stores first char of str (treated as opening quote ")
*/
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

/*function caculates the len of the tokens which consist
of different char within the str*/
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

/* skips the spaces, increments the index as long it is white space,
calculate len of token, allocation, cpy the token to allocated space and
increments the index by the len of token*/
static char	*take_token(const char *str, int *i)
{
	char	*token_str;
	int		len;

	while (is_spaceortab(str[*i]))
		*i += 1;
	len = token_len(str + *i);
	token_len = (char *)malloc(sizeof(char) * len + 1);
	ft_strcpy(token_str, str + *i, len + 1);
	*i += len;
	return (token_str);
}
