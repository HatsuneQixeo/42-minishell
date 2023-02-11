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

void	lst_print(void *token)
{
	t_token	*t;

	t = (t_token *)token;
	printf("value = (%s), type = %d\n", t->value, t->type);
}

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
	// char *input;
	// input = " !a>>>hello ---nsdsd .-n. test.txt  \" hello..tex | >> < << . -l";
	// t_list	*arr = ms_tokenize(input);
	// ft_lstiter(arr, lst_print);
	// token_list_free(&arr);

	return (EXIT_SUCCESS);
}
