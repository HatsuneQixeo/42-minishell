/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_other_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 12:05:17 by ntan-wan          #+#    #+#             */
/*   Updated: 2022/12/31 15:43:34 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
