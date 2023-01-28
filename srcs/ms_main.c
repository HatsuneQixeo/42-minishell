/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 12:10:40 by ntan-wan          #+#    #+#             */
/*   Updated: 2022/12/20 12:29:01 by ntan-wan         ###   ########.fr       */
/*                                                                           */
/* ************************************************************************** */

#include "minishell.h"

// char	*get_env_var_value(t_env *env, char *var_name);
// char    *ms_path_search(char *cmd);
// t_node	*ms_parser(char **tokens_arr);
// char	**ms_tokens_arr_create(char *input);
// int	execute_cmd(char **tokens_arr);
// int	ms_executor(t_node *node);
t_token	**ms_tokens_arr_create2(char *input);
void	ms_tokens_arr_free2(t_token ***tokens_arr);
t_list	*ms_tokenize(char *input);
void	lst_print(void *token);

int	main(int ac, char **av, char **envp)
{
	// t_env	*env;

	// env = ms_env_init(envp);
	// util_clear_screen();
	// ms_signals_handler();
	// ms_routine_run();

	// //
	// ms_env_free(&env);



	/* test token */
	
	// 1.
	// char *str = "echo hello>>test.txt";
	// t_token **arr = ms_tokens_arr_create2(str);
	// int i = -1;
	// while (arr[++i])
	// 	printf("value = %s, type = %d\n", arr[i]->value, arr[i]->type);
	// ms_tokens_arr_free2(&arr);

	// 2.
	char *input;
	
	// input = "echo hello>>    cd .    test.txt";
	input = "    	echo test>>     .txt         |   <>   << test>>a.txt      	 		a";
	t_list	*arr = ms_tokenize(input);
	ft_lstiter(arr, lst_print);
	// ms_tokens_arr_free2(&arr);
	
	// char *path;

	// path = ms_path_search("echo");
	// printf("%s\n",path);
	// free(path);

	// char *str;
	// char **tokens_arr;
	// str = "brother from another mother hheheeh dsf sff";
	// tokens_arr = ms_tokens_arr_create(str);
	// t_node *node;
	// node = ms_parser(tokens_arr);
	// // printf("%s\n", node->first_child->val.str);
	// ms_executor(node);
	// ms_tokens_arr_free(&tokens_arr);
	// ms_node_tree_free(node);

	// printf("ARG_MAX: %ld\n", sysconf(_SC_ARG_MAX));
	// printf("ARG_MAX: %d\n", ARG_MAX);
	return (EXIT_SUCCESS);
}
