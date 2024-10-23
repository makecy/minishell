/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 09:45:34 by psostari          #+#    #+#             */
/*   Updated: 2024/10/23 19:44:15 by mstefano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	check_if_redirection(int c)
{
	return (c == '<' || c == '>');
}


int	check_if_quote(int c)
{
	return (c == '\'' || c == '"');
}

int	is_special_char(int c)
{
	if (c == ' ' || c == '\t' || check_if_operator(c))
		return (TRUE);
	return (FALSE);
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
