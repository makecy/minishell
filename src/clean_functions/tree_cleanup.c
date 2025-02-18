/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_cleanup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:04:48 by psostari          #+#    #+#             */
/*   Updated: 2024/12/22 21:28:22 by mstefano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_clean_shell(void)
{
	t_env_var	*current;
	t_env_var	*next;

	if (!g_lobal_shell.envlst)
		return ;
	current = g_lobal_shell.envlst;
	while (current)
	{
		next = current->next;
		if (current->name)
			free(current->name);
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
	g_lobal_shell.envlst = NULL;
}

void	ft_clear_tree(t_tree_node **root)
{
	if (*root == NULL)
		return ;
	ft_clear_tree(&(*root)->left_child);
	ft_clear_tree(&(*root)->right_child);
	free((*root)->value);
	free(*root);
	*root = NULL;
}
