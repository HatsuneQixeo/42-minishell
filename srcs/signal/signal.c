/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 18:52:49 by hqixeo            #+#    #+#             */
/*   Updated: 2023/03/16 02:21:41 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "signal.h"

void	sig_show(int idunno)
{
	ft_dprintf(2, "sig: %d\n", idunno);
}

void	termios_ctrl(int showctrl)
{
	struct termios	term;

	if (tcgetattr(0, &term) == -1)
		return ;
	if (showctrl == TERMSHOW)
		term.c_lflag |= ECHOCTL;
	else if (showctrl == TERMHIDE)
		term.c_lflag &= ~ECHOCTL;
	else
		ft_dprintf(2, "Invalid value in termios_ctrl: %d\n", showctrl);
	tcsetattr(0, TCSANOW, &term);
}

void	sig_discardline(int sig)
{
	ft_putchar_fd('\n', 2);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_lastexit = 1;
	(void)sig;
}

void	mssig_default(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}
