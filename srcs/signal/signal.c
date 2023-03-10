/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 18:52:49 by hqixeo            #+#    #+#             */
/*   Updated: 2023/03/07 15:22:17 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "ms_common.h"

void	sig_show(int idunno)
{
	ft_dprintf(2, "sig: %d\n", idunno);
}

void	sig_discardline(int sig)
{
	ft_putchar_fd('\n', 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_lastexit = 1;
	(void)sig;
}

void	mssig_readline(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_discardline);
}

void	mssig_parent(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
}

void	mssig_heredoc(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_DFL);/* interrupt, return from executing the program */
}

void	mssig_default(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}
