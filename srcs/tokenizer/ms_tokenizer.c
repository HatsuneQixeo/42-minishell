/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:03:58 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/02/21 01:10:35 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_token.h"

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

/* 
	@brief Tokenize user input.
	@note Separate each character of input into individual token.
	@note Each character will then be assigned a token type.
	@note Eg: "abc" becomes 'a'->'b'->'c'
 */
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
