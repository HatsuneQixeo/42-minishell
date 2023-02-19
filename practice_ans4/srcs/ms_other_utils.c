/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_other_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 21:35:59 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/02/15 11:06:03 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_other_utils.h"

void	util_clear_screen(void)
{
	const char	*clear_screen;

	clear_screen = "\e[1;1H\e[2J";
	write(1, clear_screen, 10);
}

void	util_del_arr_str(void *arr_str)
{
	int		i;
	char	**arr;

	i = -1;
	arr = arr_str;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

char	**util_list_to_arr_str(t_double_list *literal_list)
{
	int		i;
	char	**arr;
	int		size_arr;

	i = -1;
	size_arr = double_lstsize(literal_list);
	arr = malloc(sizeof(char *) * (size_arr + 1));
	if (!arr)
		return (NULL);
	while (literal_list)
	{
		arr[++i] = ft_strdup(literal_list->content);
		literal_list = literal_list->next;
	}
	arr[size_arr] = NULL;
	return (arr);
}