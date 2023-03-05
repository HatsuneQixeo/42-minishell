/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:21:06 by hqixeo            #+#    #+#             */
/*   Updated: 2023/02/27 16:12:50 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	valid_syntax(const t_token *token)
{
	static const int	syntax_table[][TOKENCOUNT] = {
	{00, 00, 00, -1, 00},
	{00, -1, -1, -1, -1},
	{00, 00, -1, 00, -1},
	{00, 00, -1, 00, -1},
	{-1, 00, 00, -1, 00}
	};
	static int			prev_type = CTRL;

	if (syntax_table[prev_type][token->type] == -1)
	{
		ms_errlog("syntax error near unexpected token `%s'\n", token->value);
		prev_type = CTRL;
		g_lastexit = 258;
		return (-1);
	}
	prev_type = token->type;
	return (0);
}

int	parser_syntax(t_list *lst_token)
{
	while (lst_token != NULL)
	{
		if (valid_syntax(lst_token->content) == -1)
			return (-1);
		lst_token = lst_token->next;
	}
	return (valid_syntax(&(t_token){CTRL, "newline"}));
}
