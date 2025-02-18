/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:51:04 by psostari          #+#    #+#             */
/*   Updated: 2024/12/22 21:12:05 by mstefano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strtrim(const char *s)
{
	const char	*start;
	const char	*end;
	char		*trimmed;
	size_t		len;

	if (!s)
		return (NULL);
	start = s;
	while (*start && (*start == ' ' || *start == '\t'))
		start++;
	end = start + ft_strlen(start);
	while (end > start && (*(end - 1) == ' ' || *(end - 1) == '\t'))
		end--;
	len = end - start;
	trimmed = malloc(len + 1);
	if (!trimmed)
		return (NULL);
	ft_strlcpy(trimmed, start, len + 1);
	return (trimmed);
}

void	ft_handle_sign_and_spaces(const char *s, int *i, int *sign)
{
	while (s[*i] && (s[*i] == ' ' || s[*i] == '\t'))
		(*i)++;
	if (s[*i] == '+' || s[*i] == '-')
	{
		if (s[*i] == '-')
			*sign *= -1;
		(*i)++;
	}
}

int	ft_isnumber(const char *str)
{
	if (*str == '\0')
		return (0);
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

static int	ft_atoi_exit(const char *s)
{
	int					i;
	int					sign;
	unsigned long long	calculated_value;

	i = 0;
	sign = 1;
	calculated_value = 0;
	ft_handle_sign_and_spaces(s, &i, &sign);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			break ;
		calculated_value = (calculated_value * 10) + (s[i] - '0');
		if (calculated_value > LONG_MAX)
		{
			ft_txt_error((t_error){ENO_EXEC_255, ERR_NUM_REQUIRED, s});
			return (255);
		}
		i++;
	}
	return ((calculated_value * sign) % 256);
}

int	ft_exit(char **args)
{
	int	exit_code;

	exit_code = g_lobal_shell.exit_code;
	if (!args || !args[1])
	{
		ft_clean_shell();
		exit(exit_code);
	}
	if (args[1] && args[2])
	{
		ft_error_txt((t_error){ENO_GENERAL, ERR_ARG_OVERLOAD, NULL});
		return (1);
	}
	if (!ft_isnumber(args[1]))
	{
		ft_txt_error((t_error){ENO_EXEC_255, ERR_NUM_REQUIRED, args[1]});
		ft_clean_shell();
		exit(255);
	}
	exit_code = ft_atoi_exit(args[1]);
	ft_clean_shell();
	exit(exit_code);
}
