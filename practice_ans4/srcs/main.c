/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:14:42 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/02/13 22:23:41 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ms_btree.h"
#include "ms_ast.h"

int main()
{
	t_node			*root;
	t_double_list	*list;
	char			*input;

	root = NULL;
	// char *input = readline("test->");
	input = "echo hello>>test.txt";
	list = ms_tokenizer(input);
	ms_token_list_concat_same_type(&list);
	ast_create(&root, list);
	// debug_token_list_content_print(list);
	debug_ast_content_print(root, 0);
	ast_free(&root);
	// btree_free(&root, del);
	ms_token_list_free(&list);
}