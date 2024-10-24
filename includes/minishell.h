/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psostari <psostari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:31:53 by psostari          #+#    #+#             */
/*   Updated: 2024/10/24 12:10:54 by psostari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
	T_OR,
	T_AND,
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

//TOKENIZING
int		quote_span(const char *str);
int		token_len(const char *str);
t_token	*take_token(const char *str, int *i);
t_token	*tokenize_input(char *input);

//UTILS
int		check_if_redirection(int c);
int		check_if_quote(int c);
int		is_special_char(int c);
int		is_spaceortab(int c);
void	ft_print_quote_err(char c);

//TOKEN UTILS
int		check_if_operator(int c);
t_token	*ft_new_token(char *value, t_token_type type);
void	ft_token_list_add_back(t_token **lst, t_token *new_token);
void	ft_clear_token_list(t_token **lst);
#endif
