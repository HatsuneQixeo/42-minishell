/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_token_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:03:58 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/02/19 09:30:53 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_token.h"

t_grammar	*ms_token_grammar_get(void)
{
	static t_grammar	grammar[] = {
	{'<', TOKEN_REDIR_LEFT},
	{'>', TOKEN_REDIR_RIGHT},
	{'&', TOKEN_SEP_AND},
	{';', TOKEN_SEP_SEMICOLON},
	{'\'', TOKEN_QUOTE_SINGLE},
	{'\"', TOKEN_QUOTE_DOUBLE},
	{' ', TOKEN_SPACE},
	{'\f', TOKEN_SPACE},
	{'\n', TOKEN_SPACE},
	{'\r', TOKEN_SPACE},
	{'\t', TOKEN_SPACE},
	{'\v', TOKEN_SPACE},
	{'\\', TOKEN_BACKSLASH},
	{'$', TOKEN_VARIABLE},
	{'|', TOKEN_PIPELINE},
	};

	return (grammar);
}

t_token_type	ms_token_type_identify(char c)
{
	t_grammar	*grammar;

	grammar = ms_token_grammar_get();
	while ((*grammar).value)
	{
		if (c == (*grammar).value)
			return ((*grammar).type);
		grammar++;
	}
	return (TOKEN_LITERAL);
}

void	token_type_set(t_token *token, t_token_type type)
{
	token->type = type;
}

t_token_type	token_type_get(t_token *token)
{
	return (token->type);
}

void	*token_value_get(t_token *token)
{
	return (token->value);
}

t_token	*ms_token_create(void *value, t_token_type type)
{
	t_token	*token;	

	token = malloc(sizeof(t_token));
	if (!token || !value)
		return (NULL);
	token->value = value;
	token->type = type;
	return (token);
}

t_double_list	*ms_tokenizer(char *input)
{
	char			buf[2];
	t_token_type	type;
	char			*value;
	t_token			*token;
	t_double_list	*token_list;

	token_list = NULL;
	while (*input)
	{
		buf[0] = *input;
		buf[1] = '\0';
		value = ft_strdup(buf);
		type = ms_token_type_identify(buf[0]);
		token = ms_token_create(value, type);
		double_lstadd_back(&token_list, double_lstnew(token));
		input++;
	}
	return (token_list);
}

void	rm_token_value(t_token *token)
{
	if (!token)
		return ;
	if (token->value)
	{
		ft_bzero(token->value, 1);
		token->type = TOKEN_LITERAL;
	}
}

void	ms_token_free(void	*token)
{
	t_token	*t;

	t = token;
	free(t->value);
	free(t);
}

void	ms_token_free_del(void *token, void (*del)(void *))
{
	t_token	*t;

	t = token;
	del(t->value);
	free(t);
}

void	ms_token_list_free(t_double_list **token_list)
{
	double_lstclear(token_list, ms_token_free);
}
