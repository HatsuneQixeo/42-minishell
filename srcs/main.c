/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 12:10:40 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/02/25 10:21:06 by hqixeo           ###   ########.fr       */
/*                                                                           */
/* ************************************************************************** */

#include "minishell.h"

#ifndef SAN
# define SAN	0
#endif

void	leakcheck(const char *str)
{
	char	buffer[39];

	if (SAN != 0)
		return ;
	ft_printf("\nleakcheck: %s\n", str);
	snprintf(buffer, sizeof(buffer), "leaks -q %d >&2", getpid());
	system(buffer);
}

void	ms_signals_handler(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
}

/*
	Is oldpwd inherited for the program execution?
*/
int	main(int argc, char **argv, char **envp)
{
	ft_printf("\e[1;1H\e[2J");
	ms_signals_handler();
	ms_input(envp);
	leakcheck("mainend");
	(void)argc;
	(void)argv;
}
