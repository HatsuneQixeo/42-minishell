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
// void	*ft_realloc(void *ptr, size_t new_size);
char	**tokens_array_create(char *input);
// char	**tokens_array_create2(char *input);
char	*ms_strtok(char *str, char *delimiter);

int	main(int ac, char **av, char **envp)
{
	int i;
	char *str;

	char **arr;
	str = "hello world     my name is wang";
	arr = tokens_array_create(str);

	i = -1;
	while (arr[++i])
		printf("%s\n", arr[i]);
	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
	return (EXIT_SUCCESS);
	
}

