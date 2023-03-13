/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:14:42 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/13 20:40:56 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_ast			*ast;
	char			*input;
	t_double_list	*envp_list;
	t_double_list	*token_list;

	input = "echo a ; echo b";
	// input = "ls | cat | a";
	// input = "ls | cat | wc | wc";
	g_exit_status = 0;
	envp_list = envp_init(envp);
	token_list = ms_tokenizer(input);
	ast = ms_parser(token_list);
	envp_set(envp_list);

	// util_clear_screen();
	// debug_list_content_print(token_list, debug_token_content_print);
	debug_print_ast(ast, 0);

	ms_executor_prototype(ast);
	ast_delete(&ast);
	envp_free(&envp_list);
	return (0);
}