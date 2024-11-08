/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:31:53 by psostari          #+#    #+#             */
/*   Updated: 2024/11/08 16:09:03 by mstefano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../Libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>

#define MAX_TOKENS 1024
#define MAX_EXPANSION_SIZE 1024
#define MAX_VAR_LENGTH 255

typedef enum e_token_type {
    COMMAND,
    ARGUMENT,
    PIPE,
    REDIRECT_IN,
    REDIRECT_OUT,
    REDIRECT_APPEND,
    REDIRECT_HEREDOC,
    VARIABLE
} t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef struct s_redirection {
    char *type;
    char *file;
    struct s_redirection *next;
} t_redirection;

typedef struct s_command {
	char **args;
	t_redirection *redirections;
	struct s_command *next;
} t_command;

//TOKENIZING
int		quote_span(const char *str);
int		token_len(const char *str);
char	*take_token(const char *str, int *i);
char	**tokenize_input(char *input);

//UTILS
int		check_if_redirection(int c);
int		check_if_quote(int c);
bool	is_special_char(int c);
int		is_spaceortab(int c);
void	ft_print_quote_err(char c);


//TOKEN UTILS
int		check_if_operator(int c);
t_token	*ft_new_token(char *value, t_token_type type);
void	ft_token_list_add_back(t_token **lst, t_token *new_token);
void	ft_clear_token_list(t_token **lst);

// PARSING
char		*read_input(void);
void		parse_tokens_recursive(char **tokens, int index);
void		parse_tokens(char **tokens);
void		parse_redirections(char **tokens, t_command *command);
char		*expand_env_vars(char *input);
t_command	*parse_commands(char **tokens);
t_token_type categorize_token(char *token);

// PARSING UTILS
char	*ft_strndup(const char *src, size_t n);
char	**append_arg(char **args, char *new_arg);
int		is_valid_var_char(char c, int is_first_char);

// EXECUTION
void wait_for_child(pid_t pid);
void execute_command(char **tokens);

#endif
