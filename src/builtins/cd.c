/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 09:22:30 by psostari          #+#    #+#             */
/*   Updated: 2024/12/22 21:09:28 by mstefano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	change_to_home(void)
{
	char	*home_directory;
	char	*current_pwd;

	current_pwd = ft_get_envlst_val("PWD");
	if (current_pwd)
		set_environment_variable("OLDPWD", current_pwd, false);
	home_directory = ft_get_envlst_val("HOME");
	if (!home_directory)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (1);
	}
	if (chdir(home_directory) == 0)
	{
		set_environment_variable("PWD", home_directory, false);
		return (0);
	}
	return (1);
}

static int	display_cd_error(const char *directory)
{
	struct stat	path_stat;

	if (stat(directory, &path_stat) == 0)
	{
		if (!S_ISDIR(path_stat.st_mode))
			ft_putstr_fd("minishell: cd: not a directory\n", 2);
		else
			ft_putstr_fd("minishell: cd: permission denied\n", 2);
	}
	return (1);
}

int	ft_cd(char *directory)
{
	char	*current_pwd;
	char	*new_pwd;

	if (!directory)
		return (change_to_home());
	current_pwd = getcwd(NULL, 0);
	if (!current_pwd)
		return (1);
	if (chdir(directory) != 0)
	{
		free(current_pwd);
		return (display_cd_error(directory));
	}
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		free(current_pwd);
		return (1);
	}
	set_environment_variable("OLDPWD", current_pwd, true);
	set_environment_variable("PWD", new_pwd, true);
	free(current_pwd);
	free(new_pwd);
	return (0);
}
