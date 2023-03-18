/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 01:16:00 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/18 21:31:57 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
	@brief Group token of same type together.
	@note Eg: 'l','s' -> "ls".
 */
t_double_list	*tokenlist_regroup(t_double_list *token_list)
{
	t_token			*token;
	t_token_type	type;
	t_double_list	*list;

	list = token_list;
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
	return (token_list);
}

/* 
	@brief Filter out reject_type.
	@note Return a new memory allocated list.
 */
t_double_list	*tokenlist_filter(t_double_list *list, t_token_type reject_type)
{
	t_token			*token;
	t_double_list	*old_list;
	t_double_list	*new_list;

	old_list = list;
	new_list = NULL;
	while (list)
	{
		token = list->content;
		if (token->type != reject_type)
			double_lstadd_back(&new_list, double_lstnew(token_dup(token)));
		list = list->next;
	}
	return (new_list);
}

void	handle_backslash(t_double_list *backslash)
{
	t_token	*next_token;

	if (!backslash)
		return ;
	if (backslash->next)
	{
		next_token = backslash->next->content;
		token_type_set(next_token, LITERAL);
	}
	rm_token_value(backslash->content);
}

void	handle_variable(t_double_list *variable)
{
	t_double_list	*next;
	char			*token_value;

	next = variable->next;
	if (next && token_type_get(next->content) == LITERAL)
	{
		token_value = token_value_get(next->content);
		if (!ft_strncmp(token_value, "?", 1))
			token_type_set(next->content, EXPAND);
		else
			list_token_type_set(next, EXPAND);
		rm_token_value(variable->content);
	}
	else
		token_type_set(variable->content, LITERAL);
}

void	handle_quote(t_double_list *quote)
{
	t_token			*token;
	t_token_type	quote_type;
	t_double_list	*next;
	t_double_list	*quote_pair[2];

	next = quote->next;
	quote_pair[0] = quote;
	quote_type = token_type_get(quote->content);
	while (next)
	{
		token = next->content;
		if (token->type == token_type_get(quote->content))
			break ;
		else if (quote_type == DOUBLE_QUOTE && token->type == BACKSLASH)
			handle_backslash(next);
		else if (quote_type == DOUBLE_QUOTE && token->type == VARIABLE)
			handle_variable(next);
		else if (token->type != LITERAL && token->type != EXPAND)
			token_type_set(token, LITERAL);
		next = next->next;
	}
	quote_pair[1] = next;
	rm_token_value(quote_pair[0]->content);
	rm_token_value(quote_pair[1]->content);
}
