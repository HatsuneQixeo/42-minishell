/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 16:12:50 by hqixeo            #+#    #+#             */
/*   Updated: 2023/03/11 23:21:27 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "ms_common.h"
# include "token.h"

enum e_lexertoken
{
	DEFAULT,
	RDRT,
	CTRL,
	SUBSH_BEGIN,
	SUBSH_END,
	TOKENCOUNT
};

char	*ms_closequote(const char *raw);

void	lstshow_lexertoken(void *content);

/* Lexer */
t_list	*ms_lexer(const char *raw);

#endif
