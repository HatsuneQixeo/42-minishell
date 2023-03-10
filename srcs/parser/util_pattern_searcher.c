/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_pattern_searcher.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 01:53:32 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/10 10:15:08 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
	@brief Find whether input matches any given patterns.
	@param pattern_func array of function pointers that check matching pattern.
	@param scanner stores the token list.
	@return t_ast * is returned upon success, else return NULL.
 */
t_ast	*pattern_searcher(t_ast *(*pattern_func[])(t_parser *), t_parser *p)
{
	int				i;
	t_ast			*new_node;
	t_double_list	*initial_cursor;

	i = -1;
	new_node = NULL;
	initial_cursor = p->scanner->cursor;
	while (!new_node && pattern_func[++i])
	{
		new_node = (pattern_func[i])(p);
		if (!new_node)
			p->scanner->cursor = initial_cursor;
	}
	return (new_node);
}
