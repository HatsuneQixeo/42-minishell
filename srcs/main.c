/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:14:42 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/03 14:35:22 by ntan-wan         ###   ########.fr       */
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

/* ********** SCANNER ********** */

void	scanner_free(t_scanner **self);

/* ********** PARSER ********** */

int		parse_cmd_word(t_scanner *scanner, t_cmd_word **cmd_word);
void	cmd_word_free(t_cmd_word **cmd_word);
int		parse_cmd_name(t_scanner *scanner, t_cmd_name **cmd_name);
void	cmd_name_free(t_cmd_name **cmd_name);
int		parse_file_name(t_scanner *scanner, t_file_name **file_name);
void	file_name_free(t_file_name **file_name);
void	here_end_free(t_here_end **here_end);
int		parse_here_end(t_scanner *scanner, t_here_end **here_end);

void	io_here_free(t_io_here **io_here);
int		parse_io_here(t_scanner *scanner, t_io_here **io_here);
void	io_file_free(t_io_file **io_file);
int		parse_io_file(t_scanner *scanner, t_io_file **io_file);
void	io_redir_free(t_io_redirect **io_redir);
int		parse_io_redirect(t_scanner *scanner, t_io_redirect **io_redir);

void	cmd_prefix_io_redir_free(t_double_list **cmd_prefix_io_redir);
int		parse_cmd_prefix_io_redir(t_scanner *scanner, t_cmd_prefix *cmd_prefix);

int		cmd_prefix_add(t_scanner *scanner, t_cmd_prefix *cmd_prefix);
void	cmd_prefix_free(t_cmd_prefix **cmd_prefix);

int		parse_cmd_prefix(t_scanner *scanner, t_cmd_prefix **cmd_prefix);
int		parse_simple_cmd_prefix(t_scanner *scanner, t_simple_cmd *simple_cmd);

int		parse_simple_cmd(t_scanner *scanner, t_simple_cmd **simple_cmd);

t_double_list	*scanner_next(t_scanner *self);
void	simple_cmd_free(t_simple_cmd **simple_cmd);

int	main(int ac, char **av, char **envp)
{
	char			*input;
	t_double_list	*token_list;
	t_scanner		*scanner;
	
	input = ">a";
	token_list = ms_tokenizer(input);
	parse_token_list(token_list);
	scanner = scanner_init(token_list);

	// debug_list_content_print(token_list, debug_token_content_print);

	// while (scanner->current_list)
	// {
		int	status;

		// t_cmd_word	*cmd_word;
		// status = parse_cmd_word(scanner, &cmd_word);
		// cmd_word_free(&cmd_word);

		// t_cmd_name *cmd_name;
		// status = parse_cmd_name(scanner, &cmd_name);
		// cmd_name_free(&cmd_name);

		// t_file_name *file_name;
		// status = parse_file_name(scanner, &file_name);
		// file_name_free(&file_name);

		// t_here_end *here_end;
		// status = parse_here_end(scanner, &here_end);
		// here_end_free(&here_end);

		// t_io_here	*io_here;
		// status = parse_io_here(scanner, &io_here);
		// io_here_free(&io_here);

	// t_io_file	*io_file;
	// status = parse_io_file(scanner, &io_file);
	// io_file_free(&io_file);

	// t_io_redirect	*io_redir;
	// status = parse_io_redirect(scanner, &io_redir);
	// io_redir_free(&io_redir);
	
	// t_cmd_prefix	*cmd_prefix;
	// cmd_prefix = ft_calloc(1, sizeof(t_cmd_prefix));
	// parse_cmd_prefix_io_redir(scanner, cmd_prefix);
	// cmd_prefix_io_redir_free(&cmd_prefix->io_redirect);
	// free(cmd_prefix);

	// t_cmd_prefix	*cmd_prefix;
	// cmd_prefix = ft_calloc(1, sizeof(t_cmd_prefix));
	// cmd_prefix_add(scanner, cmd_prefix);
	// cmd_prefix_free(&cmd_prefix);
	// free(cmd_prefix);

 	// t_cmd_prefix	*cmd_prefix;
	// status = parse_cmd_prefix(scanner, &cmd_prefix);
	// cmd_prefix_free(&cmd_prefix);

	// t_cmd_prefix	*cmd_prefix;
	// t_simple_cmd	*simple_cmd;
	// simple_cmd = ft_calloc(1, sizeof(t_simple_cmd));
	// status = parse_simple_cmd_prefix(scanner, simple_cmd);
	// free(simple_cmd);

	t_simple_cmd	*simple_cmd;
	status = parse_simple_cmd(scanner, &simple_cmd);
	simple_cmd_free(&simple_cmd);
	printf("status %d\n", status);
	// }
	scanner_free(&scanner);
	return (0);
}