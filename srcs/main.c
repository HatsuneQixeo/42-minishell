/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:14:42 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/10 13:00:52 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	resources_free(char **input, t_double_list **lst, t_node **ast)
// {
// 	if (*input)
// 	{
// 		free(*input);
// 		*input = NULL;
// 	}
// 	if (*lst)
// 		token_list_free(lst);
// 	if (*ast)
// 		ast_delete(ast);
// }

// haven't handle signal
// int main(int ac, char **av, char **envp)
// {
// 	t_double_list	*env;
// 	char			*input;
// 	t_node			*ast_root;
// 	t_double_list	*token_list;

// 	input = NULL;
// 	ast_root = NULL;
// 	token_list = NULL;
// 	env = env_init(envp);
// 	env_set_or_get(env);
// 	util_clear_screen();
// 	while (true)
// 	{
// 		input = readline("🐚 $ ");
// 		if (input && ft_strncmp(input, "exit", 4))
// 		{
// 			add_history(input);
// 			token_list = ms_tokenizer(input);
// 			ast_root = ms_parser(token_list);
// 			ms_executor(ast_root);
// 			//
// 			// debug_list_content_print(token_list, debug_token_content_print);
// 			debug_ast_content_print(ast_root, 0);
// 			//
// 			resources_free(&input, &token_list, &ast_root);
// 		}
// 		else
// 			break ;
// 	}
// 	resources_free(&input, &token_list, &ast_root);
// 	env_free(&env);

// }

int	ast_gettype(t_ast *node)
{
	return (node->type & (~AST_DATA));
}

void	print_ast(t_ast *root, int indent)
{
	int		i;
	int		node_type_int;
	char	*node_type_str;

	i = -1;
	// printf("%d\n", indent);
	if (!root)
		return ;
	while (++i < indent)
		printf(" ");
	node_type_str = "(null)";
	node_type_int = ast_gettype(root);
	if (node_type_int & AST_RD_HDOC)
		node_type_str = "<<";
	else if (node_type_int & AST_RD_INFILE)
		node_type_str = "<";
	else if (node_type_int & AST_RD_APPEND)
		node_type_str = ">>";
	else if (node_type_int & AST_RD_TRUNC)
		node_type_str = ">";
	else if (node_type_int & AST_ARG)
		node_type_str = "arg";
	else if (node_type_int & AST_CMD)
		node_type_str = "cmd";
	else if (node_type_int & AST_PIPE)
		node_type_str = "|";
	else if (node_type_int & AST_AND)
		node_type_str = "&&";
	else if (node_type_int & AST_OR)
		node_type_str = "||";
	if (root->type & AST_DATA)
		printf("type: %s, data: %s\n", node_type_str, root->data);
	else
		printf("type: %s\n", node_type_str);
	print_ast(root->left, indent + 4);
	print_ast(root->right, indent + 4);
}

t_double_list	*tokenlist_regroup(t_double_list *token_list);;

int	main(int ac, char **av, char **envp)
{
	char			*input;
	t_double_list	*token_list;
	t_ast			*ast;

	input = "(echo helo | echo hi)";
	token_list = ms_tokenizer(input);
	ast = ms_parser(token_list);

	// debug_list_content_print(token_list, debug_token_content_print);

	print_ast(ast, 0);
	ast_delete(&ast);
	return (0);
}