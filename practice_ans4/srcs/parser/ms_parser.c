/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:54:55 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/02/19 14:22:38 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_token.h"
#include "ms_double_linked_list.h"
#include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

// bool	has_matching_quote(t_double_list *quote_list, t_token_type quote_type)
// {
// 	t_token	*token;
// 	int		quote_count;

// 	quote_count = 0;
// 	while (quote_list)
// 	{
// 		token = quote_list->content;
// 		if (token->type == quote_type)
// 			quote_count++;
// 		quote_list = quote_list->next;
// 	}
// 	return (quote_count % 2 == 0);
// }

// void	get_input_and_add_to_list(t_double_list *quote_list)
// {
// 	char	*add_on_input;
// 	t_token	*token_quote;

// 	token_quote = quote_list->content;
// 	while (!has_matching_quote(quote_list, token_quote->type))
// 	{
// 		double_lstlast(quote_list)->next = ms_tokenizer("\n");
// 		add_on_input = readline("> ");
// 		double_lstlast(quote_list)->next = ms_tokenizer(add_on_input);
// 		free(add_on_input);
// 	}
// }

void	handle_backslash(t_double_list *backslash)
{
	t_token	*next_token;

	if (!backslash)
		return ;
	if (backslash->next)
	{
		next_token = backslash->next->content;
		token_type_set(next_token, TOKEN_LITERAL);
	}
	rm_token_value(backslash->content);
}

void	list_token_type_set(t_double_list *list, t_token_type set_type)
{
	t_token_type	init_type;
	t_token_type	type;

	if (!list)
		return ;
	init_type = token_type_get(list->content);
	while (list)
	{
		type = token_type_get(list->content);
		if (type != init_type)
			break ;
		else
			token_type_set(list->content, set_type);
		list = list->next;
	}
}

void	handle_variable(t_double_list *variable)
{
	t_double_list	*next;
	char			*token_value;
	
	next = variable->next;
	if (next && token_type_get(next->content) == TOKEN_LITERAL)
	{
		token_value = token_value_get(next->content);
		if (!ft_strncmp(token_value, "?", 1))
			token_type_set(next->content, TOKEN_EXPAND);
		else
			list_token_type_set(next, TOKEN_EXPAND);
		rm_token_value(variable->content);
	}
	else
		token_type_set(variable->content, TOKEN_LITERAL);
}

void	handle_quote(t_double_list *quote, bool *in_quote)
{
	*in_quote = !*in_quote;
	rm_token_value(quote->content);
}

void	ms_parser2(t_double_list *list)
{
	t_token_type	type;
	bool			in_single_quote;
	bool			in_double_quote;
	
	in_single_quote = false;
	in_double_quote = false;
	while (list)
	{
		type = token_type_get(list->content);
		if (!in_double_quote && type == TOKEN_QUOTE_SINGLE)
			handle_quote(list, &in_single_quote);
		else if (!in_single_quote && type == TOKEN_QUOTE_DOUBLE)
			handle_quote(list, &in_double_quote);
		else if (!in_single_quote && type == TOKEN_BACKSLASH)
			handle_backslash(list);
		else if (!in_single_quote && type == TOKEN_VARIABLE)
			handle_variable(list);
		else if (in_single_quote || in_double_quote && type != TOKEN_EXPAND)
			token_type_set(list->content, TOKEN_LITERAL);
		list = list->next;
	}
}
