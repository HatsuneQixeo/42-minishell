/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:54:55 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/10 16:43:38 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_token_type_same_concat(t_double_list *token_list)
{
	t_token	*token;
	t_token	*next_token;
	t_token	*new_token;

	while (token_list && token_list->next)
	{
		token = token_list->content;
		next_token = token_list->next->content;
		if (token->type == next_token->type)
		{
			new_token = concat_2_tokens(token, next_token, token->type);
			token_list->content = new_token;
			token_free(token);
			double_lstdelone(token_list->next, token_free);
			if (token_is_operator(new_token))
				break ;
		}
		else
			break ;
	}
}

void	parse_token_type_reassign(t_double_list *token_list)
{
	t_token	*token;
	char	*value;

	if (!token_list)
		return ;
	token = token_list->content;
	value = token->value;
	if (ft_strlen(value) == 2)
	{
		if (token->type == PIPELINE)
			token_type_set(token, OR);
		else if (token->type == AMPERSAND)
			token_type_set(token, AND);
		else if (token->type == LESS)
			token_type_set(token, DLESS);
		else if (token->type == GREAT)
			token_type_set(token, DGREAT);
		else if (token->type == SEMICOLON)
			token_type_set(token, UNKNOWN);
	}
}

t_parser	*parser_init(t_double_list *token_list)
{
	t_parser	*p;

	p = ft_calloc(1, sizeof(t_parser));
	if (p)
	{
		p->scanner = s_init(token_list);
		p->and_or_ast = ft_calloc(1, sizeof(t_ast *));
	}
	return (p);
}

void	parser_free(t_parser **p)
{
	s_free(&(*p)->scanner);
	free((*p)->and_or_ast);
	free((*p));
	*p = NULL;
}

t_ast	*ms_parser(t_double_list *token_list)
{
	t_parser		*p;
	t_ast			*ast;

	tokenlist_regroup(token_list);
	p = parser_init(tokenlist_filter(token_list, SPACES));
	ast = parse_cmdline(p);
	if (p->scanner->cursor != NULL)
	{
		util_perror("syntax error: ", s_get_token(p->scanner)->value);
		ast_delete(&ast);
	}
	parser_free(&p);
	return (ast);
}
