/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:21:06 by hqixeo            #+#    #+#             */
/*   Updated: 2023/02/25 10:21:06 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	echo_isflag(const char *str)
{
	if (*str++ != '-')
		return (0);
	while (*str == 'n')
		str++;
	return (*str == '\0');
}

void	iteristr_echo(int i, char *str)
{
	if (i != 0)
		ft_putchar_fd(' ', 1);
	ft_putstr_fd(str, 1);
}

int	ms_echo(char **argv, t_data *data)
{
	int	nl;

	ft_printf("it's me echo!\n");
	nl = 1;
	while (*++argv != NULL && echo_isflag(*argv))
		nl = 0;
	ft_strlistiteri(argv, iteristr_echo);
	if (nl)
		ft_putchar_fd('\n', 1);
	return (0);
	(void)data;
}
