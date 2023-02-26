/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:14:42 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/02/25 10:46:33 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	resources_free(char **input, t_double_list **lst, t_node **ast)
{
	if (*input)
	{
		free(*input);
		*input = NULL;
	}
	if (*lst)
		token_list_free(lst);
	if (*ast)
		ast_free(ast);
}

// haven't handle signal
int main(int ac, char **av, char **envp)
{
	t_double_list	*env;
	char			*input;
	t_node			*ast_root;
	t_double_list	*token_list;

	input = NULL;
	ast_root = NULL;
	token_list = NULL;
	env = env_init(envp);
	env_set_or_get(env);
	util_clear_screen();
	while (true)
	{
		input = readline("🐚 $ ");
		if (input && ft_strncmp(input, "exit", 4))
		{
			add_history(input);
			token_list = ms_tokenizer(input);
			ast_root = ms_parser(token_list);
			ms_executor(ast_root);
			//
			// debug_list_content_print(token_list, debug_token_content_print);
			debug_ast_content_print(ast_root, 0);
			//
			resources_free(&input, &token_list, &ast_root);
		}
		else
			break ;
	}
	resources_free(&input, &token_list, &ast_root);
	env_free(&env);
	return (0);
}