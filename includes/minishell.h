/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 00:08:07 by mstefano          #+#    #+#             */
/*   Updated: 2024/12/23 20:29:45 by mstefano         ###   ########.fr       */
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
# include <fcntl.h>
# include <termios.h>
# include <limits.h>
# include <sys/stat.h>

# define ENO_SUCCESS 0
# define MAX_TOKENS 1024
# define BUFFER_SIZE 1024
# define MAX_EXPANSION_SIZE 1024
# define MAX_VAR_LENGTH 256

typedef enum e_token_type
{
	T_IDENTIFIER,
	T_PIPE,
	T_REDIRECTION,
	T_OR,
	T_AND,
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef struct s_env_var
{
	char					*name;
	char					*value;
	struct s_env_var		*next;
}	t_env_var;

typedef enum s_error_message
{
	ERR_CMD_NOT_FOUND,
	ERR_FILE_NOT_EXIST,
	ERR_PERMISSION_DENIED,
	ERR_REDIRECTION_ISSUE,
	ERR_ARG_OVERLOAD,
	ERR_NUM_REQUIRED
}	t_error_message;

typedef enum s_err_type
{
	SUCCESS_CODE,
	ENO_GENERAL,
	ENO_CANT_EXEC = 126,
	ENO_NOT_FOUND,
	ENO_EXEC_255 = 255
}	t_err_type;

typedef struct s_error
{
	t_err_type		error_code;
	t_error_message	error_type;
	const char		*error_details;
}	t_error;

typedef struct s_tree_node
{
	char				*value;
	struct s_tree_node	*left_child;
	struct s_tree_node	*right_child;
}	t_tree_node;

typedef struct s_minishell
{
	t_env_var		*envlst;
	int				exit_code;
	struct termios	original_term;
	t_tree_node		*tree_root;
}	t_minishell;

typedef struct s_redirection
{
	char					*type;
	char					*file;
	struct s_redirection	*next;
}	t_redirection;

typedef struct s_command
{
	char				**args;
	t_redirection		*redirections;
	struct s_command	*next;
}	t_command;

extern char			**environ;

extern t_minishell	g_lobal_shell;

// TOKENIZING
int			quote_span(const char *str);
int			token_len(const char *str);
char		*take_token(const char *str, int *i);
char		**tokenize_input(const char *input_line, int i, int err);

// CHECK UTILS
int			check_if_redirection(int c);
int			check_if_quote(int c);
int			is_special_char(int c);
int			is_spaceortab(int c);
void		ft_print_quote_err(char c);

// TOKEN UTILS
int			check_if_operator(int c);
void		ft_token_list_add_back(t_token **lst, t_token *new_token);
void		ft_clear_token_list(t_token **lst);
t_token		*ft_new_token(char *value, t_token_type type);
char		*parse_quoted_token(const char *input, int *i, int *error_flag);
void		free_tokens_on_error(char **tokens, int token_index);

// BUILTINS
int			ft_pwd(void);
int			ft_cd(char *directory);
int			ft_echo(char **args);
int			ft_env(void);
char		*ft_retrieve_key(char *str);
char		*ft_retrive_value(char *str);
void		ft_init_envlst(void);

// UTILS
char		*ft_get_envlst_val(char *name);
void		*ft_memory_box(void *ptr, bool clean);
void		ft_env_var_to_end(t_env_var *new);
void		set_environment_variable(char *name, char *value, bool create);
char		*ft_strcpy(char *dest, const char *src);
char		*ft_strcat(char *dest, const char *src);
void		ft_putstr_fd_const(const char *s, int fd);

// EXPORT
int			ft_export(char **argv);
int			export_err(char *name);
int			name_check(const char *name);
void		ft_export_list(void);
void		export_var(const char *name, const char *value);
void		parse_name_value(const char *arg, char **name, char **value);
void		process_export_arg(char *name, char *value, int *exit_status);
void		add_new_var(const char *name, const char *value);
void		update_existing_var(t_env_var *var, const char *value);

// EXIT
void		ft_handle_sign_and_spaces(const char *s, int *i, int *sign);
int			ft_exit(char **args);
int			ft_isnumber(const char *str);
char		*ft_strtrim(const char *s);

// UNSET
void		ft_remove_env_var(t_env_var **head, const char *name);
int			ft_unset(char **args);

// EXECUTION UTILS

bool		ft_find_env_variable(char *name);
int			ft_strcmp(const char *s1, const char *s2);
int			check_if_operator(int c);
void		ft_del(void *data);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_token_list_add_back(t_token **lst, t_token *new_token);
void		ft_clear_token_list(t_token **lst);
t_token		*ft_new_token(char *value, t_token_type type);

// EXEC_BUILTINS
int			ft_is_builtin(char *arg);
int			ft_builtin_exec(char **args);

// CLEAN FUNCTIONS
void		ft_clean_environment_list(void);
void		ft_clean_shell(void);
void		ft_clear_tree(t_tree_node **root);

// FREEING

void		free_pipeline(t_command *pipeline);
void		free_redirection(t_redirection *redir);
void		free_command(t_command *command);
void		free_tokens(char **tokens);

// ERROR
int			ft_error_txt(t_error error);
int			ft_txt_error(t_error error);

// EXPAND

char		*expand_exit_status(char *input, int last_exit_status);
char		*expand_env_variables(char *input, char **envp);
char		*get_env_value(const char *key, char **envp);

// PARSING
char		*read_input(void);
char		**append_arg(char **args, char *new_arg);
void		parse_tokens_recursive(char **tokens, int index);
void		parse_tokens(char **tokens);
void		free_tokens(char **tokens);
void		execute_pipeline(t_command *commands, char **envp);
t_command	*parse_commands(char **tokens);

// UTILS_PARSE
char		**create_initial_args(char *new_arg);
void		parse_redirections_for_commands(t_command *head);
void		handle_pipe_token(t_command **current);
t_command	*create_new_command(void);

// EXECUTION

void		wait_for_child(pid_t pid);
void		execute_command(t_command *command);
void		execute_builtin(char **tokens, t_command *command);
void		exec_external_command(char **tokens, char **envp, int i);

// REDIRECTION

void		handle_heredoc(const char *delimiter);
void		apply_input_redirection(t_redirection *redir);
void		apply_output_redirection(t_redirection *redir);
void		parse_redirections(char **tokens, t_command *command);
int			handle_redirections(t_command *command);
int			is_redirection_token(const char *token);

// REDIR_UTILS
void		count_arguments(char **tokens, size_t *arg_count);
char		**allocate_new_args(size_t arg_count);
int			handle_redirection_token(char **tokens, size_t *i,
				t_command *command, char **new_args);
void		read_heredoc_lines(int pipefd[2], const char *delimiter);

#endif
