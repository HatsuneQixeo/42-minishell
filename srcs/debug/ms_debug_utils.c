/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_debug_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:01:23 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/13 06:58:18 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug_token_content_print(void *content)
{
	t_token	*t;	

	t = content;
	printf("value -> %s\n", (char *)t->value);
	printf("type -> %d\n", t->type);
}

void	debug_env_content_print(void *content)
{
	char	*env_str;

	env_str = content;
	printf("%s\n", env_str);
}

void	debug_list_content_print(t_double_list *list, void (*f)(void *))
{
	double_lstiter(list, f);
}

void	debug_ast_content_print(t_node *root, int indent)
{
	int		i;
	t_token	*token;
	char	**token_value;

	if (!root)
		return ;
	i = -1;
	token = root->content;
	token_value = token->value;
	while (++i < indent)
		printf(" ");
	i = -1;
	while (token_value[++i])
		printf("%s ", token_value[i]);
	printf("\n");
	debug_ast_content_print(root->left, indent + 2);
	debug_ast_content_print(root->right, indent + 2);
}

void	debug_print_ast(t_ast *root, int indent)
{
	int					i;
	char				*node_type_str;
	const t_key_value	key_value[] = {
		{AST_RD_HDOC, "<<"},
		{AST_RD_INFILE, "<"},
		{AST_RD_APPEND, ">>"},
		{AST_RD_TRUNC, ">"},
		{AST_ARG, "arg"},
		{AST_CMD, "cmd"},
		{AST_PIPE, "|"},
		{AST_AND, "&&"},
		{AST_OR, "||"},
		{0, 0}
	};

	if (!root)
		return ;
	i = -1;
	while (++i < indent)
		printf(" ");
	i = -1;
	while (key_value[++i].key)
	{
		if (ast_gettype(root) & key_value[i].key)
			node_type_str = key_value[i].value;
	}
	if (root->type & AST_DATA)
		printf("type: %s, data: %s\n", node_type_str, root->data);
	else
		printf("type: %s\n", node_type_str);
	debug_print_ast(root->left, indent + 4);
	debug_print_ast(root->right, indent + 4);
}