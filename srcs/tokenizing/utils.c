/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 09:45:34 by psostari          #+#    #+#             */
/*   Updated: 2024/10/22 18:50:06 by mstefano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*if c is < or > */
int	check_if_redirection(int c)
{
	if (c == '<' || c == '>')
		return (TRUE);
	return (FALSE);
}

/*if c is operator(|)*/
int	check_if_operator(int c)
{
	if (check_if_redirection(c) || c == '|')
		return (TRUE);
	return (FALSE);
}

//true is char is ' or ""
int	check_if_quote(int c)
{
	if (c == '\'' || c == '"')
		return (TRUE);
	return (FALSE);
}

/*true if c is space tab or < , > or |*/
int	is_special_char(int c)
{
	if (c == ' ' || c == '\t' || check_if_operator(c))
		return (TRUE);
	return (FALSE);
}

int	is_spaceortab(int c)
{
	if (c == ' ' || c == '\t')
		return (TRUE);
	return (FALSE);
}
