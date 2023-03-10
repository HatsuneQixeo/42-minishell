/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 08:35:52 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/09 20:23:29 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
	@return t_ast * is returned upon success, else return NULL.
	@note Pass array of redir pattern functions to pattern_searcher()
	@note    for finding matching pattern.
 */
t_ast	*parse_redir(t_parser *p)
{
	static t_ast	*(*redir_pattern_funcs[])(t_parser *) = {
		parse_redir_in,
		parse_redir_out,
		NULL
	};

	return (pattern_searcher(redir_pattern_funcs, p));
}
