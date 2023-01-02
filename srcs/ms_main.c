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

// char	*ms_tokenize(char *str, char *delimiter);
void	*ft_realloc(void *ptr, size_t new_size);
char	**tokens_array_create(char *input);
char	**tokens_array_create2(char *input);
char	*ms_strtok(char *str, char *delimiter);

int	main(int ac, char **av, char **envp)
{
	// t_env	*env;

	// env = ms_env_init(envp);
	// ms_signals_handler();
	// util_clear_screen();
	// ms_routine_run();
	// printf("%ld\n", strspn("abcde", "a"));
	// int		i = -1;
	// char *str;
	// str = "hello everyone in this";
	// char *token;
	// char *str;
	// char *delimiter;

	// char *str;
	// char *delimiter;
	// char *token;
	// str = "hello world this is      ,me               and";
	// delimiter = " ,";
	// token = ms_strtok(str, delimiter);
	// while (token)
	// {
	// 	printf("%s\n", token);
	// 	free(token);
	// 	token = ms_strtok(NULL, delimiter);
	// }
	char *str;

	str = "hello world my name is wang";
	char **arr;
	// arr = NULL;
	// arr = tokens_array_create(str);
	arr = tokens_array_create(str);
	int i;

	i = -1;
	// while (arr[++i]) {
	// 	printf("%s\n", arr[i]);
	// }
	// i = -1;
	// // while (++i < 2)
	while (arr[++i])
	{
		// free(arr[i]);
		printf("%d\n", i);
		printf("%s\n", arr[i]);
	}
	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);

	// int *arr;

	// arr = malloc(sizeof(int) * 4);

	// arr[0] = 0;
	// arr[1] = 1;
	// arr[2] = 2;
	// arr[3] = 3;

	// // ft_realloc(arr, 5 * sizeof(int));

	// int	*c_ptr;
	// int i;

	// c_ptr = arr;
	// i = -1;
	// while (c_ptr[++i])
	// {
	// 	printf("value %d\n", c_ptr[i]);
	// 	// printf("size %d\n", i + 1);
	// }
	// printf("size %d\n", i + 1);

	// char	**str;

	// str = NULL;
	// str = ft_realloc(str, 0, 1 * sizeof(char *));
	// str[0] = "hello";
	// str = ft_realloc(str, 1 * sizeof(char *), (2) * sizeof(char *));
	// str[1] = "world";
	// str = ft_realloc(str, 2 * sizeof(char *), (4) * sizeof(char *));
	// str[2] = "wangsdfdsfdsf";
	// printf("%s\n", str[0]);
	// printf("%s\n", str[1]);
	// printf("%s\n", str[2]);
	// // free(str[0]);
	// // free(str[1]);
	// free(str);

	// printf("%s\n", str[1]);
	return (EXIT_SUCCESS);
}

