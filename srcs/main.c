/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:14:42 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/09 11:39:44 by ntan-wan         ###   ########.fr       */
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

// t_ast	*cmd_ast(t_ast *node);

void	parse_token_list2(t_double_list **list);

// t_sh	*mini_sh_init()
// {
// 	t_sh	*mini_sh;

// 	mini_sh->scanner = s_init();
// 	mini_sh = malloc(sizeof(t_sh));
// 	mini_sh->cmd_ast = ft_calloc(1, sizeof(t_ast));
// 	mini_sh->and_or_ast = ft_calloc(1, sizeof(t_ast));
// 	return (mini_sh);
// }

int	main(int ac, char **av, char **envp)
{
	char			*input;
	t_double_list	*token_list;
	t_sh			*sh;
	// t_scanner		*scanner;

	input = "echo <a <b c d";
	token_list = ms_tokenizer(input);
	parse_token_list2(&token_list);
	// scanner = s_init(token_list);
	sh = ft_calloc(1, sizeof(t_sh));
	sh->scanner = s_init(token_list);

	// debug_list_content_print(token_list, debug_token_content_print);

	t_ast	*node;
	
	// node = parse_redir_in(scanner);

	// node = parse_redir_out(scanner);

	// node = parse_redir(sh);
	node = parse_tokenlist(sh);
	// node = token_list_test_1(scanner);
	// node = token_list_test_2(scanner);
	// node = parse_tokenlist(scanner);
	// node = parse_cmd(scanner);
	// node = parse_tokenlist(scanner);
	// node = parse_job(scanner);
	// node = parse_cmdline(mini_sh);
	print_ast(node, 0);
	// print_ast(cmd_ast(NULL), 0);
	// print_ast(*and_or_ast(NULL), 0);
	if (sh->scanner->cursor)
		printf("syntax error near unexpexcted token '%s'\n", (char *)token_value_get(sh->scanner->cursor->content));
	// s_free(&mini_sh->scanner);
	return (0);
}