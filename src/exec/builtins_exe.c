/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 11:14:24 by psostari          #+#    #+#             */
/*   Updated: 2024/12/22 21:32:28 by mstefano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_builtin_exec(char **args)
{
	if (ft_strcmp(args[0], "echo") == 0)
		return (ft_echo(args));
	if (ft_strcmp(args[0], "cd") == 0)
		return (ft_cd(args[1]));
	if (ft_strcmp(args[0], "env") == 0)
		return (ft_env());
	if (ft_strcmp(args[0], "exit") == 0)
		return (ft_exit(args));
	if (ft_strcmp(args[0], "pwd") == 0)
		return (ft_pwd());
	if (ft_strcmp(args[0], "export") == 0)
		return (ft_export(args));
	if (ft_strcmp(args[0], "unset") == 0)
		return (ft_unset(args));
	return (ENO_GENERAL);
}

int	ft_is_builtin(char *arg)
{
	if (!arg)
		return (0);
	if (!ft_strcmp(arg, "echo") || !ft_strcmp(arg, "cd")
		|| !ft_strcmp(arg, "exit") || !ft_strcmp(arg, "pwd")
		|| !ft_strcmp(arg, "export") || !ft_strcmp(arg, "unset")
		|| !ft_strcmp(arg, "env"))
		return (1);
	return (0);
}

void	ft_putstr_fd_const(const char *s, int fd)
{
	ft_putstr_fd((char *)s, fd);
}
