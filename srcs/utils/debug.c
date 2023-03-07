/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:21:07 by hqixeo            #+#    #+#             */
/*   Updated: 2023/03/07 15:22:17 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_common.h"

# ifndef DBG_ERRNO
#  define DBG_ERRNO	0
# endif

#ifndef SAN
# define SAN	0
#endif

#ifndef DEBUG
# define DEBUG	1
#endif

void	leakcheck(const char *str)
{
	char	buffer[39];

	if (SAN || !DEBUG)
		return ;
	ft_dprintf(2, "\nleakcheck: %s\n", str);
	snprintf(buffer, sizeof(buffer), "leaks -q %d >&2", getpid());
	system(buffer);
}

void	leakfd(const char *str)
{
	int	arrfd[100];
	int	fd_expect;

	if (!DEBUG)
		return ;
	ft_dprintf(2, "\nleakfd: %s\n", str);
	fd_expect = 3;
	for (int i = 0; i < 100 && fd_expect < 1024 && fd_expect != -1; i++)
	{
		arrfd[i] = open("/dev/null", O_RDONLY);
		if (arrfd[i] == -1)
		{
			perror("/dev/null");
			break ;
		}
		if (arrfd[i] != fd_expect)
			ft_dprintf(2, "fdleak: %d-%d\n", fd_expect, arrfd[i] - 1);
		fd_expect = arrfd[i] + 1;
	}
	for (int i = 0; i < 100; i++)
		close(arrfd[i]);
}

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
	if (!DBG_ERRNO || !DEBUG)
		return ;
	ft_dprintf(2, "%s errno: %d\n", name, g_lastexit);
}
