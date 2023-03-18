/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_scanner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 01:06:54 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/18 09:16:11 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_scanner	*s_init(t_double_list *token_list)
{
	t_scanner	*scanner;

	scanner = malloc(sizeof(t_scanner));
	if (scanner)
	{
		scanner->token_list = token_list;
		scanner->cursor = token_list;
	}
	return (scanner);
}

/* 
	@brief Get current token from scanner.
	@return Return pointer to t_token.
 */
t_token	*s_get_token(t_scanner *scanner)
{
	if (scanner->cursor)
		return (scanner->cursor->content);
	else
		return (NULL);
}

/* 
	@brief Read the next list and advance the cursor.
	@return Return next list.
*/
t_double_list	*s_next(t_scanner *scanner)
{
	if (scanner->cursor)
		scanner->cursor = scanner->cursor->next;
	return (scanner->cursor);
}

/* 
	@brief If current token matches match_type, advance scanner's cursor.
 */
bool	s_match_and_consume_token(t_token_type match_type, t_scanner *s)
{
	if (s_token_type_matches(match_type, s))
	{
		s_next(s);
		return (true);
	}
	else
		return (false);
}

/* 
	@brief Check whether the current token matches match_type.
 */
bool	s_token_type_matches(t_token_type match_type, t_scanner *s)
{
	return (s_get_token(s) && s_get_token(s)->type == match_type);
}
