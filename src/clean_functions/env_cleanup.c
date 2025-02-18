/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cleanup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psostari <psostari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:59:16 by psostari          #+#    #+#             */
/*   Updated: 2024/11/26 13:54:06 by psostari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_clean_environment_list(void)
{
	t_env_var	*envlst;
	t_env_var	*envlst_tofree;

	envlst = g_lobal_shell.envlst;
	while (envlst)
	{
		envlst_tofree = envlst;
		envlst = envlst->next;
		free(envlst_tofree->name);
		free(envlst_tofree->value);
		free(envlst_tofree);
	}
	g_lobal_shell.envlst = NULL;
}
