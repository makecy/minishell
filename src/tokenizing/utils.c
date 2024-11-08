/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:40:36 by psostari          #+#    #+#             */
/*   Updated: 2024/11/08 13:29:38 by mstefano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_if_redirection(int c)
{
	return (c == '<' || c == '>');
}

int	check_if_quote(int c)
{
	return (c == '\'' || c == '"');
}

bool	is_special_char(int c)
{
	  return (c == '|' || c == '>' || c == '<' || c == '&' || c == ';');
}

int	is_spaceortab(int c)
{
	return (c == ' ' || c == '\t');
}

void	ft_print_quote_err(char c)
{
	fprintf(stderr, "minishell: unexpected EOF \
	while looking for matching `%c`\n", c);
}
