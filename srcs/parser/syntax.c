/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:21:06 by hqixeo            #+#    #+#             */
/*   Updated: 2023/03/07 15:22:16 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	syntax_table_init(int **syntax_table)
{
	syntax_table[DEFAULT] = (int [TOKENCOUNT]){00, 00, 00, -1, 00};
	syntax_table[RDRT] = (int [TOKENCOUNT]){00, -1, -1, -1, -1};
	syntax_table[CTRL] = (int [TOKENCOUNT]){00, 00, -1, 00, -1};
	syntax_table[SUBSH_BEGIN] = (int [TOKENCOUNT]){00, 00, -1, 00, -1};
	syntax_table[SUBSH_END] = (int [TOKENCOUNT]){-1, 00, 00, -1, 00};
}

static int	valid_syntax(int **syntax_table, const t_token *token)
{
	static int	prev_type = CTRL;

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
	int	syntax_table[TOKENCOUNT][TOKENCOUNT];

	syntax_table_init((int **)syntax_table);
	while (lst_token != NULL)
	{
		if (valid_syntax((int **)syntax_table, lst_token->content) == -1)
			return (-1);
		lst_token = lst_token->next;
	}
	return (valid_syntax((int **)syntax_table, &(t_token){CTRL, "newline"}));
}
