/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:14:42 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/18 21:33:28 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_screen(void)
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

void	run_minishell_process(char *input)
{
	t_ast			*ast;
	t_double_list	*token_list;

	if (!input)	
		return ;
	token_list = ms_tokenizer(input);
	ast = ms_parser(token_list);
	ms_executor(ast);
	ast_delete(&ast);
	token_list_free(&token_list);
}

// haven't handle subshell.
// haven't handle expander.
// haven't handle expander in heredoc.
// haven't handle signal.
// haven't handle builtin cmds.
// haven't handle unclosed quote.
// haven't handle print err message for g_exit_status_update.
// check heredoc signal process.
int	main(int ac, char **av, char **envp)
{
	char	*input;

	clear_screen();
	signal_handler_parent_process();
	minishell_init(ac, av, envp);
	while (1)
	{
		// 
		signal_handler_parent_process();
		input = readline("🐚 $ ");
		if (input)
		{
			run_minishell_process(input);
			free(input);
		}
		else
		{
			envp_free();
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			exit(g_exit_status);
		}
	}
	return (0);
}