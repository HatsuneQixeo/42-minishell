/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token_getter_setter.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 00:30:13 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/02/21 00:55:50 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_token.h"

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
