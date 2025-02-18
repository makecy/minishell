/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 09:10:48 by psostari          #+#    #+#             */
/*   Updated: 2024/12/23 20:26:32 by mstefano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_minishell	g_lobal_shell = {NULL, 0, {0}, NULL};

void	free_tokens_on_error(char **tokens, int token_index)
{
	while (--token_index >= 0)
		free(tokens[token_index]);
	free(tokens);
}

static void	handle_exit_command(t_command *commands, char **tokens, char *input,
		char *expanded_input)
{
	int	status;

	status = ft_exit(commands->args);
	free_command(commands);
	free_tokens(tokens);
	free(input);
	free(expanded_input);
	if (status == 1)
		return ;
	exit(status);
}

static void	process_input(char *input, char **envp)
{
	char		*expanded_input;
	char		**tokens;
	t_command	*commands;

	expanded_input = expand_exit_status(input, g_lobal_shell.exit_code);
	expanded_input = expand_env_variables(expanded_input, envp);
	tokens = tokenize_input(expanded_input, 0, 0);
	commands = parse_commands(tokens);
	if (commands && commands->args && commands->args[0])
	{
		if (ft_strcmp(commands->args[0], "exit") == 0)
			handle_exit_command(commands, tokens, input, expanded_input);
		else if (ft_is_builtin(commands->args[0]))
			g_lobal_shell.exit_code = ft_builtin_exec(commands->args);
		else if (commands->next == NULL)
			execute_command(commands);
		else
			execute_pipeline(commands, envp);
	}
	else
		execute_pipeline(commands, envp);
	free_command(commands);
	free_tokens(tokens);
	free(expanded_input);
}

static void	main_loop(char **envp)
{
	char	*input;

	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (*input)
			add_history(input);
		process_input(input, envp);
		free(input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	ft_init_envlst();
	main_loop(envp);
	return (0);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	char		*input;
// 	char		**tokens;
// 	char		*expanded_input;
// 	int			last_exit_status;
// 	int			status;
// 	t_command	*commands;

// 	(void)argc;
// 	(void)argv;
// 	ft_init_envlst();
// 	while (1)
// 	{
// 		input = readline("minishell> ");
// 		if (!input)
// 		{
// 			printf("exit\n");
// 			break ;
// 		}
// 		if (*input)
// 			add_history(input);
// 		last_exit_status = 0;
// 		expanded_input = expand_exit_status(input, last_exit_status);
// 		expanded_input = expand_env_variables(expanded_input, envp);
// 		tokens = tokenize_input(expanded_input);
// 		commands = parse_commands(tokens);
// 		if (commands && commands->args && commands->args[0])
// 		{
// 			if (ft_strcmp(commands->args[0], "exit") == 0)
// 			{
// 				status = ft_exit(commands->args);
// 				free_command(commands);
// 				free_tokens(tokens);
// 				free(input);
// 				free(expanded_input);
// 				if (status == 1)
// 					continue ;
// 			}
// 			if (ft_is_builtin(commands->args[0]))
// 				g_lobal_shell.exit_code = ft_builtin_exec(commands->args);
// 			if (commands->next == NULL)
// 				execute_command(commands);
// 			else
// 				execute_pipeline(commands, envp);
// 		}
// 		else
// 			execute_pipeline(commands, envp);
// 		free_command(commands);
// 		free_tokens(tokens);
// 		free(input);
// 		free(expanded_input);
// 	}
// 	return (0);
// }
