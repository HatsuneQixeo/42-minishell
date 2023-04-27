/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:22:18 by hqixeo            #+#    #+#             */
/*   Updated: 2023/03/16 02:21:42 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef SIGNAL_H
# define SIGNAL_H

# include "ms_common.h"
# include <signal.h>
# include <termios.h>

# define TERMHIDE	0
# define TERMSHOW	1

void	sig_show(int idunno);
void	sig_discardline(int sig);

void	termios_ctrl(int showctrl);

void	mssig_default(void);

#endif
