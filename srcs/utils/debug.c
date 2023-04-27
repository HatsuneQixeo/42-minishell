/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:21:07 by hqixeo            #+#    #+#             */
/*   Updated: 2023/03/16 02:21:42 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ms_common.h"

#ifndef SAN
# define SAN	0
#endif

#ifndef DEBUG
# define DEBUG	0
#endif

#define FDTEST_SIZE	100

void	leakcheck(const char *dummy)
{
	(void)dummy;
}

void	leakfd(const char *dummy2)
{
	(void)dummy2;
}

// void	leakcheck(const char *str)
// {
// 	char	buffer[39];

// 	if (SAN || !DEBUG)
// 		return ;
// 	ft_dprintf(2, RED"\nleakcheck: %s\n"DEF, str);
// 	snprintf(buffer, sizeof(buffer), "leaks -q %d >&2", getpid());
// 	/* Forbidden */
// 	ft_putstr_fd(GREY, 2);
// 	system(buffer);
// 	ft_putstr_fd(DEF, 2);
// }

// void	leakfd(const char *str)
// {
// 	int	arrfd[FDTEST_SIZE];
// 	int	fd_expect;

// 	if (!DEBUG || FDTEST_SIZE <= 0)
// 		return ;
// 	ft_dprintf(2, RED"\nleakfd: %s\n"DEF, str);
// 	fd_expect = 3;
// 	for (unsigned int i = 0; i < FDTEST_SIZE; i++)
// 	{
// 		arrfd[i] = open("/dev/null", O_RDONLY);
// 		if (arrfd[i] == -1)
// 		{
// 			perror("/dev/null");
// 			for (unsigned int i_clear = 0; i_clear < i; i++)
// 				close(arrfd[i_clear]);
// 			return ;
// 		}
// 		if (arrfd[i] != fd_expect)
// 			ft_dprintf(2, RED"fdleak: %d-%d\n"DEF, fd_expect, arrfd[i] - 1);
// 		fd_expect = arrfd[i] + 1;
// 	}
// 	if (arrfd[FDTEST_SIZE - 1] == FDTEST_SIZE + 2)
// 		ft_dprintf(2, GREEN"No fd leaks\n"DEF);
// 	for (int i = 0; i < FDTEST_SIZE; i++)
// 		close(arrfd[i]);
// }

void	lstshow_tmpname(t_list *lst, t_ftsetname ft_setname,
			const char *tmpname, t_ftiterlst ft_debug)
{
	const char	*name = ft_setname(NULL);

	ft_setname(tmpname);
	ft_lstiter(lst, ft_debug);
	ft_setname(name);
}

void	debug_errno(const char *name)
{
	if (!DEBUG)
		return ;
	ft_dprintf(2, "%s errno: %d\n", name, g_lastexit);
}
