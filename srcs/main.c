/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:14:42 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/18 14:29:24 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	util_clear_screen(void)
{
	const char	*clear_screen;

	clear_screen = "\e[1;1H\e[2J";
	write(1, clear_screen, 10);
}

void	minishell_init(int ac, char **argv, char **envp)
{
	t_double_list	*envp_list;

	(void)ac;
	(void)argv;
	g_exit_status = 0;
	envp_list = envp_init(envp);
	envp_set(envp_list);
}

// haven't handle subshell.
// haven't handle expander.
// haven't handle expander in heredoc.
// haven't handle signal.
// haven't handle builtin cmds.
// haven't handle unclosed quote.
// haven't handle print err message for g_exit_status_update.
int	main(int ac, char **av, char **envp)
{
	t_ast			*ast;
	char			*input;
	t_double_list	*token_list;

	util_clear_screen();
	minishell_init(ac, av, envp);
	while (1)
	{
		input = readline("🐚 $ ");
		token_list = ms_tokenizer(input);
		ast = ms_parser(token_list);
		ms_executor(ast);
		//
		// debug_print_ast(ast, 0);
		// debug_list_content_print(token_list, debug_token_content_print);
		free(input);
		ast_delete(&ast);
	}
	free(input);
	//remember to free envp when necessary...
	// envp_free(&envp_list);
	return (0);
}