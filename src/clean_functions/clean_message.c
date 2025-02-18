/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psostari <psostari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:41:25 by psostari          #+#    #+#             */
/*   Updated: 2024/11/26 13:54:00 by psostari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cleanup_shell(void)
{
	ft_memory_box(NULL, true);
	ft_clear_tree(&g_lobal_shell.tree_root);
	ft_clean_environment_list();
	tcsetattr(STDIN_FILENO, TCSANOW, &g_lobal_shell.original_term);
}
