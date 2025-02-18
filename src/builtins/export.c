/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:10:05 by psostari          #+#    #+#             */
/*   Updated: 2024/12/22 21:25:55 by mstefano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_new_var(const char *name, const char *value)
{
	t_env_var	*new;

	new = malloc(sizeof(t_env_var));
	if (!new)
		return ;
	new->name = ft_strdup(name);
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = NULL;
	new->next = NULL;
	ft_env_var_to_end(new);
}

void	update_existing_var(t_env_var *var, const char *value)
{
	free(var->value);
	if (value)
		var->value = ft_strdup(value);
	else
		var->value = NULL;
}

void	ft_export_list(void)
{
	t_env_var	*list;
	size_t		i;

	list = g_lobal_shell.envlst;
	while (list)
	{
		printf("declare -x %s=\"", list->name);
		i = 0;
		while (list->value && list->value[i])
		{
			if (list->value[i] == '$' || list->value[i] == '"')
				printf("\\%c", list->value[i]);
			else
				printf("%c", list->value[i]);
			i++;
		}
		printf("\"\n");
		list = list->next;
	}
}

static int	handle_export_arg(char *arg)
{
	char	*name;
	char	*value;
	int		status;

	status = 0;
	parse_name_value(arg, &name, &value);
	if (!name_check(name))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		status = 1;
	}
	else
		set_environment_variable(name, value, true);
	free(name);
	free(value);
	return (status);
}

int	ft_export(char **argv)
{
	int	i;
	int	exit_status;

	if (!argv[1])
	{
		ft_export_list();
		return (0);
	}
	exit_status = 0;
	i = 1;
	while (argv[i])
	{
		if (handle_export_arg(argv[i]))
			exit_status = 1;
		i++;
	}
	return (exit_status);
}
