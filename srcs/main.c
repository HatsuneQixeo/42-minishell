/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:14:42 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/02/23 00:00:36 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// haven't handle signal
int main(int ac, char **av, char **envp)
{
	// char			*input;
	// t_node			*ast_root;
	// t_double_list	*token_list;
	
	// input = NULL;
	// token_list = NULL;
	// ast_root = NULL;
	// util_clear_screen();
	// while (true)
	// {
	// 	input = readline("🐚 $ ");
	// 	if (input && ft_strncmp(input, "exit", 4))
	// 	{
	// 		add_history(input);
	// 		token_list = ms_tokenizer(input);
	// 		ast_root = ms_parser(token_list);
	// 		// ms_executor(ast_root);
	// 		//
	// 		debug_list_content_print(token_list, debug_token_content_print);
	// 		debug_ast_content_print(ast_root, 0);
	// 		//
	// 		free(input);
	// 		token_list_free(&token_list);
	// 		ast_free(&ast_root);
	// 	}
	// 	else
	// 		break ;
	// }
	// free(input);
	// token_list_free(&token_list);
	// ast_free(&ast_root);


	t_double_list	*env;

	env = env_init(envp);
	env_set_or_get(env);
	char	*path = absolute_path_find("ls");
	printf("%s\n",path);
	free(path);
	env_free(&env);
	return (0);
}