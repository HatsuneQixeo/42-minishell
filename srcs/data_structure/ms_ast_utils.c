/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_ast_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:51:04 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/02/21 00:36:30 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_ast.h"

void	ast_add_token_literal(t_node **root, t_double_list *literal_list)
{
	void	*arr_str;
	void	*ptr_token;

	if (!literal_list)
		return ;
	arr_str = util_list_to_arr_str(literal_list);
	ptr_token = (void *)token_create(arr_str, LITERAL);
	btree_node_add(root, btree_node_init(ptr_token));
}

void	ast_add_token_operator(t_node **root, t_token *token)
{
	void	*arr_str;
	void	*ptr_token;	

	if (!token)
		return ;
	arr_str = ft_split(token->value, '\0');
	ptr_token = (void *)token_create(arr_str, token->type);
	btree_node_add(root, btree_node_init(ptr_token));
}

void	ast_create(t_node **root, t_double_list *token_list)
{
	t_token			*token;
	char			*value;
	t_double_list	*literal_list;

	literal_list = NULL;
	while (token_list)
	{
		token = token_list->content;
		value = token->value;
		if (token_is_separator(token))
			break ;
		else if (token_is_operator(token))
		{
			ast_add_token_literal(root, literal_list);
			double_lstclear(&literal_list, free);
			ast_add_token_operator(root, token);
		}
		else if (token->type != SPACES)
			double_lstadd_back(&literal_list, double_lstnew(ft_strdup(value)));
		token_list = token_list->next;
	}
	ast_add_token_literal(root, literal_list);
	double_lstclear(&literal_list, free);
}

void	ast_del_content_token(void *token)
{
	t_token	*t;

	t = token;
	token_free_del(token, util_del_arr_str);
}

void	ast_free(t_node **root)
{
	btree_free(root, ast_del_content_token);
}
