/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_token_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 09:10:56 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/02/12 00:02:38 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_token.h"

bool	ms_token_is_space(char c)
{
	char	*space;

	space = " \f\n\r\t\v";
	while (*space)
	{
		if (c == *space)
			return (true);
		space++;
	}
	return (false);
}

bool	ms_token_is_separator(t_token *token)
{
	t_token_type	type;

	type = token->type;
	return (type == TOKEN_SEP_AND
		|| type == TOKEN_SEP_OR || type == TOKEN_SEP_SEMICOLON);
}

bool	ms_token_is_operator(t_token *token)
{
	t_token_type	type;

	type = token->type;
	return (type >= TOKEN_PIPELINE && type <= TOKEN_REDIR_RIGHT_DOUBLE);
}

t_token	*concat_2_tokens(t_token *token_1, t_token *token_2, t_token_type type)
{
	char	*value;

	value = ft_strjoin(token_1->value, token_2->value);
	return (ms_token_create(value, type));
}

void	ms_token_list_concat_same_type(t_double_list **head)
{
	t_double_list	*curr;
	t_double_list	*next;
	t_token			*token;
	t_token			*next_token;

	curr = *head;
	while (curr && curr->next)
	{
		next = curr->next;
		token = curr->content;
		next_token = curr->next->content;
		if (token->type == next_token->type)
		{
			curr->content = concat_2_tokens(token, next_token, token->type);
			curr->next = curr->next->next;
			if (curr->next)
				curr->next->prev = curr;
			ms_token_free(token);
			double_lstdelone(next, ms_token_free);
		}
		else
			curr = curr->next;
	}
}
