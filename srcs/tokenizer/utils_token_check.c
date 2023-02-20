/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 00:37:05 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/02/21 00:55:21 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_token.h"

bool	token_is_space(char c)
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

bool	token_is_separator(t_token *token)
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
