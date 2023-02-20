/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_token_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 09:10:56 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/02/20 23:58:48 by ntan-wan         ###   ########.fr       */
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
	return (type == AMPERSAND
		|| type == OR || type == SEMICOLON);
}

bool	token_is_operator(t_token *token)
{
	t_token_type	type;

	type = token->type;
	return (type >= PIPELINE && type <= SEMICOLON);
}

t_token	*concat_2_tokens(t_token *token_1, t_token *token_2, t_token_type type)
{
	char	*value;

	value = ft_strjoin(token_1->value, token_2->value);
	return (token_create(value, type));
}
