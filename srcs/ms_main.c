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
int	ms_executor(t_node *node);
// #include <linux/limits.h>
int	main(int ac, char **av, char **envp)
{
	t_env	*env;

	env = ms_env_init(envp);
	util_clear_screen();
	ms_signals_handler();
	ms_routine_run();
	
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
