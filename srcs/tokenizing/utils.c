/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psostari <psostari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 09:45:34 by psostari          #+#    #+#             */
/*   Updated: 2024/10/23 09:59:23 by psostari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*if c is < or > */
int	check_if_redirection(int c)
{
	return (c == '<' || c == '>');
}

//true is char is ' or ""
int	check_if_quote(int c)
{
	return (c == '\'' || c == '"');
}

/*true if c is space tab or < , > or |*/
int	is_special_char(int c)
{
	return (c == ' ' || c == '\t' || check_if_operator(c));
}

int	is_spaceortab(int c)
{
	return (c == ' ' || c == '\t');
}

/*end of file*/
void	ft_print_quote_err(char c)
{
	fprintf(stderr, "minishell: unexpected EOF \
	while looking for matching `%c`\n", c);
}
