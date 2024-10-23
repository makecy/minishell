/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:33:23 by mstefano          #+#    #+#             */
/*   Updated: 2024/10/23 19:42:49 by mstefano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef TRUE
#  define TRUE 1
# endif

# ifndef FALSE
#  define FALSE 0
# endif

#define BUFFER_SIZE 1024

# include "../Libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

// TOKENIZING

int		quote_span(const char *str);
int		token_len(const char *str);
char	*take_token(const char *str, int *i);
char 	**tokenize_input(char *input);

// UTILS

int	check_if_redirection(int c);
int	check_if_operator(int c);
int	check_if_quote(int c);
int	is_special_char(int c);
int	is_spaceortab(int c);

// PARSING

char *read_input(void);
void parse_tokens_recursive(char **tokens, int index);
void parse_tokens(char **tokens);

// EXECUTION

void wait_for_child(pid_t pid);
void execute_command(char **tokens);

#endif