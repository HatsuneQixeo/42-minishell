/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_other_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 21:35:59 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/02/24 14:17:08 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	util_perror(char *title, char *msg)
{
	ft_putstr_fd(title, 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}

void	util_clear_screen(void)
{
	const char	*clear_screen;

	clear_screen = "\e[1;1H\e[2J";
	write(1, clear_screen, 10);
}

void	util_arr_str_free(void *arr_str)
{
	int		i;
	char	**arr;

	i = -1;
	arr = arr_str;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

char	**util_list_to_arr_str(t_double_list *list)
{
	int		i;
	char	**arr;
	int		size_arr;

	i = -1;
	size_arr = double_lstsize(list);
	arr = malloc(sizeof(char *) * (size_arr + 1));
	if (!arr)
		return (NULL);
	while (list)
	{
		arr[++i] = ft_strdup(list->content);
		list = list->next;
	}
	arr[size_arr] = NULL;
	return (arr);
}
