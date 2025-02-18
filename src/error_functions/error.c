/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:46:08 by psostari          #+#    #+#             */
/*   Updated: 2024/12/22 21:30:16 by mstefano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_error_txt(t_error error)
{
	if (error.error_type == ERR_CMD_NOT_FOUND)
		return (ft_putstr_fd("minishell: ", 2),
			ft_putstr_fd_const(error.error_details, 2),
			ft_putstr_fd(": command not found\n", 2), error.error_code);
	else if (error.error_type == ERR_FILE_NOT_EXIST)
		return (ft_putstr_fd("minishell: ", 2),
			ft_putstr_fd_const(error.error_details, 2),
			ft_putstr_fd(": No such file or directory\n", 2), error.error_code);
	else if (error.error_type == ERR_PERMISSION_DENIED)
		return (ft_putstr_fd("minishell: ", 2),
			ft_putstr_fd_const(error.error_details, 2),
			ft_putstr_fd(": Permission denied\n", 2), error.error_code);
	else if (error.error_type == ERR_REDIRECTION_ISSUE)
		return (ft_putstr_fd("minishell: ", 2),
			ft_putstr_fd_const(error.error_details, 2),
			ft_putstr_fd(": ambiguous redirect\n", 2), error.error_code);
	else if (error.error_type == ERR_ARG_OVERLOAD)
		return (ft_putstr_fd("minishell: exit: too many arguments\n", 2),
			error.error_code);
	return (0);
}

int	ft_txt_error(t_error error)
{
	if (error.error_type == ERR_NUM_REQUIRED)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd_const(error.error_details, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (error.error_code);
	}
	return (0);
}
