/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psostari <psostari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 10:03:19 by psostari          #+#    #+#             */
/*   Updated: 2024/10/23 11:17:05 by psostari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*head -> [ls, T_IDENTIFIER] -> [ -l, T_IDENTIFIER] -> [|, T_PIPE] ->
[grep, T_IDENTIFIER] -> ["test", T_IDENTIFIER] -> NULL,
funtion creates individual tokens that are aded to token list
*/
t_token	*ft_new_token(char *value, t_token_type type)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = value;
	new_token->type = type;
	new_token->next = NULL;
	return (new_token);
}

/*function adds new token to the end of list of tokens,
if the list is empty, it initializes it with a new token,
if the list is not empty, it traverses to the end of the list,
adds the new token at the end by updating the next pointer of the last token
*/
void	ft_token_list_add_back(t_token **lst, t_token *new_token)
{
	t_token	*curr_node;

	if (!*lst)
	{
		*lst = new_token;
		return ;
	}
	curr_node = *lst;
	while (curr_node->next)
		curr_node = curr_node->next;
	curr_node->next = new_token;
}

/*function dealocates all memory, prevents memory leaks,
1. free the memory allocated for the tokens valuse,
2. store pointer to the next token,
3. free the memory allocated for the cur toknes
4. move to next token
after everything is freed poiner is ste to NULL = lst is empty*/
void	ft_clear_token_list(t_token **lst)
{
	t_token	*curr_node;
	t_token	*next;

	curr_node = *lst;
	while (curr_node)
	{
		free(curr_node->value);
		next = curr_node->next;
		free(curr_node);
		curr_node = next;
	}
	*lst = NULL;
}
