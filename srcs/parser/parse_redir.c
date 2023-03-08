/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 08:35:52 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/08 09:30:18 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
    @note Must search the patterns in the following order.
	@return Return an array of functions that
	@return check for redir matching pattern.
 */
t_ast *(**redir_pattern_array(void))(t_scanner *)
{
	static t_ast *(*pattern_func[])(t_scanner *) = {
		parse_redir_in,
		parse_redir_out,
		NULL
	};

return (pattern_func);

}

/* 
	@return t_ast * is returned upon success, else return NULL.
 */
t_ast	*parse_redir(t_scanner *s)
{
	return (pattern_searcher(redir_pattern_array(), s));
}
