/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_token_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:03:58 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/02/20 23:59:41 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_token.h"

t_grammar	*token_grammar_get(void)
{
	static t_grammar	grammar[] = {
	{'<', REDIR_LEFT},
	{'>', REDIR_RIGHT},
	{'&', AMPERSAND},
	{';', SEMICOLON},
	{'\'', SINGLE_QUOTE},
	{'\"', DOUBLE_QUOTE},
	{' ', SPACES},
	{'\f', SPACES},
	{'\n', SPACES},
	{'\r', SPACES},
	{'\t', SPACES},
	{'\v', SPACES},
	{'\\', BACKSLASH},
	{'$', VARIABLE},
	{'|', PIPELINE},
	};

	return (grammar);
}

t_token_type	token_type_identify(char c)
{
	t_grammar	*grammar;

	grammar = token_grammar_get();
	while ((*grammar).value)
	{
		if (c == (*grammar).value)
			return ((*grammar).type);
		grammar++;
	}
	return (LITERAL);
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

t_token	*token_create(void *value, t_token_type type)
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
		type = token_type_identify(buf[0]);
		token = token_create(value, type);
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
		ft_bzero(token->value, ft_strlen(token->value));
		token->type = LITERAL;
	}
}

void	token_free(void	*token)
{
	t_token	*t;

	t = token;
	free(t->value);
	free(t);
}

void	token_free_del(void *token, void (*del)(void *))
{
	t_token	*t;

	t = token;
	del(t->value);
	free(t);
}

void	token_list_free(t_double_list **token_list)
{
	double_lstclear(token_list, token_free);
}
