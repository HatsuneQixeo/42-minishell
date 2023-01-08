/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_other_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 12:05:17 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/01/09 00:56:01 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "other_utils.h"

void	util_clear_screen(void)
{
	const char	*clear_screen;

	clear_screen = "\e[1;1H\e[2J";
	write(1, clear_screen, 10);
}

int	util_str_arr_len(char **arr)
{
	int	len;

	len = 0;
	while (*arr++)
		len++;
	return (len);
}

char	**util_str_arr_dup(char **arr)
{
	int		i;
	char	**copy;

	if (!arr)
		return (NULL);
	copy = ft_calloc(util_str_arr_len(arr) + 1, sizeof(*copy));
	i = -1;
	while (arr[++i])
		copy[i] = ft_strdup(arr[i]);
	return (copy);
}

void	*util_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	size_t	copy_size;

	if (!ptr)
		return (malloc(new_size));
	copy_size = 0;
	new_ptr = malloc(new_size);
	if (ptr && new_ptr)
	{
		if (old_size && old_size < new_size)
			copy_size = old_size;
		else
			copy_size = new_size;
		ft_memcpy(new_ptr, ptr, copy_size);
	}
	if (new_ptr || !new_size)
		free(ptr);
	return (new_ptr);
}