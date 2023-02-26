/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:21:06 by hqixeo            #+#    #+#             */
/*   Updated: 2023/02/25 18:26:22 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_common.h"

static int	echo_isflag(const char *str)
{
	if (*str++ != '-')
		return (0);
	while (*str == 'n')
		str++;
	return (*str == '\0');
}

void	iteri_echo(int i, void *str)
{
	if (i != 0)
		ft_putchar_fd(' ', 1);
	ft_putstr_fd(str, 1);
}

int	ms_echo(char **argv, t_data *data)
{
	int	nl;

	nl = 1;
	while (*++argv != NULL && echo_isflag(*argv))
		nl = 0;
	ft_strlistiteri(argv, iteri_echo);
	if (nl)
		ft_putchar_fd('\n', 1);
	return (0);
	(void)data;
}
