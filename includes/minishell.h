/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psostari <psostari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:33:23 by mstefano          #+#    #+#             */
/*   Updated: 2024/10/23 11:51:01 by psostari         ###   ########.fr       */
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

# define BUFFER_SIZE 1024

# include "../Libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_token_type {
	T_IDENTIFIER,
	T_PIPE,
	T_REDIRECTION,
	T_AND,
	T_OR,
	T_O_PARENT,
	T_C_PARENT,
	T_UNKNOWN
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

// TOKENIZING

t_token	*ft_new_token(char *value, t_token_type type);
void	ft_token_list_add_back(t_token **lst, t_token *new_token);
void	ft_clear_token_list(t_token **lst);
int		check_if_operator(const char *str);
int		quote_span(const char *str);
int		token_len(const char *str);
t_token	*take_token(const char *str, int *i);
t_token	*tokenize_input(char *input);
int		check_if_redirection(int c);
int		check_if_operator(int c);
int		check_if_quote(int c);
int		is_special_char(int c);
int		is_spaceortab(int c);
void	ft_print_quote_err(char c);

// UTILS

int		check_if_redirection(int c);
int		check_if_operator(int c);
int		check_if_quote(int c);
int		is_special_char(int c);
int		is_spaceortab(int c);

// PARSING

char	*read_input(void);
void	parse_tokens_recursive(char **tokens, int index);
void	parse_tokens(char **tokens);

// EXECUTION

void	wait_for_child(pid_t pid);
void	execute_command(char **tokens);

#endif
