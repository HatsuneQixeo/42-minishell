/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:14:42 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/02/19 03:47:27 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_parser(t_double_list **token_list);

void	ms_parser2(t_double_list *token_list);

int main()
{
	t_node			*root;
	t_double_list	*token_list;
	char			*input;

	root = NULL;
	util_clear_screen();
	input = readline("🐚 $ ");
	// input = "\"\"hello\"\"";
	token_list = ms_tokenizer(input);
	ms_parser2(token_list);
	// ms_parser2(token_list);
	// tokenlist_head_concat_same_type(&token_list, TOKEN_LITERAL);
	tokenlist_concat_same_type(&token_list);
	// ast_create(&root, token_list);
	
	debug_token_list_content_print(token_list);
	// debug_token_list_content_print(list_ptr);
	// debug_ast_content_print(root, 0);

	// ast_free(&root);
	ms_token_list_free(&token_list);
	free(input);
}