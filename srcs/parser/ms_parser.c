/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:54:55 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/05 13:03:51 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_token_type_same_concat(t_double_list *token_list)
{
	t_token	*token;
	t_token	*next_token;
	t_token	*new_token;

	while (token_list && token_list->next)
	{
		token = token_list->content;
		next_token = token_list->next->content;
		if (token->type == next_token->type)
		{
			new_token = concat_2_tokens(token, next_token, token->type);
			token_list->content = new_token;
			token_free(token);
			double_lstdelone(token_list->next, token_free);
			if (token_is_operator(new_token))
				break ;
		}
		else
			break ;
	}
}

void	parse_token_type_reassign(t_double_list *token_list)
{
	t_token	*token;
	char	*value;

	if (!token_list)
		return ;
	token = token_list->content;
	value = token->value;
	if (ft_strlen(value) == 2)
	{
		if (token->type == PIPELINE)
			token_type_set(token, OR);
		else if (token->type == AMPERSAND)
			token_type_set(token, AND);
		else if (token->type == LESS)
			token_type_set(token, DLESS);
		else if (token->type == GREAT)
			token_type_set(token, DGREAT);
		else if (token->type == SEMICOLON)
			token_type_set(token, UNKNOWN);
	}
}

// got bug, "  echo  ", create another function to generate list without spaces
void	handle_spaces(t_double_list **list, t_double_list **token_list)
{
	t_double_list *next;
	
	// while (*list && token_type_get((*list)->content) == SPACES)	
	// {
	// 	next = (*list)->next;
	// 	double_lstdelone(*list, token_free);
	// 	*list = next;
	// }
	parse_token_type_same_concat(*list);
	if (!(*list)->prev && !(*list)->next)
	{
		double_lstdelone(*list, token_free);
		*token_list = NULL;
	}
	else if (!(*list)->prev)
	{
		next = (*list)->next;
		double_lstdelone(*list, token_free);
		*list = next;
		*token_list = *list;
	}
	else
	{
		next = (*list)->next;
		double_lstdelone(*list, token_free);
		*list = next;
	}
}

// void	parse_token_remove_spaces(t_double_list **token_list)
// {
// 	t_double_list *next;
	
// 	// next = (*token_list)->next;
// 	// if (*token_list && token_type_get((*token_list)->content) == SPACES)
// 		// double_lstdelone(*token_list, token_free);
// 	// *token_list = next;
// 	// *token_list = NULL;
// }

void	parse_token_list(t_double_list *token_list)
{
	t_token			*token;
	t_token_type	type;

	while (token_list)
	{
		token = token_list->content;
		type = token->type;
		if (type == SINGLE_QUOTE || type == DOUBLE_QUOTE)
			handle_quote(token_list);
		else if (type == BACKSLASH)
			handle_backslash(token_list);
		else if (type == VARIABLE)
			handle_variable(token_list);
		// else if (type == SPACES)
			// handle_spaces(&token_list);
		// parse_token_type_same_concat(token_list);
		// parse_token_type_reassign(token_list);
		// parse_token_remove_spaces(&token_list);
		if (token_list)
			token_list = token_list->next;
	}
}

t_token	*token_dup(t_token *token)
{
	t_token	*new_token;

	if (!token)
		return (NULL);
	new_token = ft_calloc(1, sizeof(t_token));
	new_token->value = ft_strdup(token->value);
	new_token->type = token->type;
	return (new_token);
}

t_double_list	*token_list_filter(t_double_list *list, t_token_type type)
{
	t_token			*token;
	t_double_list	*old_list;
	t_double_list	*new_list;
	
	old_list = list;
	new_list = NULL;
	while (list)	
	{
		token = list->content;
		if (token->type != type)
			double_lstadd_back(&new_list, double_lstnew(token_dup(token)));
		list = list->next;
	}
	double_lstclear(&old_list, token_free);
	return (new_list);
}

void	parse_token_list2(t_double_list **token_list)
{
	t_token			*token;
	t_token_type	type;
	t_double_list	*list;

	list = *token_list;
	while (list)
	{
		token = list->content;
		type = token->type;
		if (type == SINGLE_QUOTE || type == DOUBLE_QUOTE)
			handle_quote(list);
		else if (type == BACKSLASH)
			handle_backslash(list);
		else if (type == VARIABLE)
			handle_variable(list);
		parse_token_type_same_concat(list);
		parse_token_type_reassign(list);
		list = list->next;
	}
	*token_list = token_list_filter(*token_list, SPACES);
}
// haven't handle separator.
// haven't handle syntax check.
// haven't handle subshell.
// haven't handle unclosed quote/and_or operator
// haven't handle multiple redirection.
// Plan to do syntax checking by checking the ast
t_node	*ms_parser(t_double_list *token_list)
{
	t_node	*root;

	root = NULL;
	parse_token_list(token_list);
	ast_create(&root, token_list);
	return (root);
}
