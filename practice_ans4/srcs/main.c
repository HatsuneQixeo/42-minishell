/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:14:42 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/02/13 21:48:08 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ms_btree.h"

void	ast_create(t_node **root, t_double_list *token_list);
void	ast_free(t_node **root);
void	btree_free(t_node **node, void (*del)(void *));

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