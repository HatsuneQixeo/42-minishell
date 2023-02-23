/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_common.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 00:52:27 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/01/09 03:27:24 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_COMMON_H
# define MS_COMMON_H

# include "libft.h"

int	g_lastexit;

int		ft_isquote(int c);
int		ft_isnameletter(int c);
void	ft_cleanterminal(void);
int		ft_dup3(int fd_attribute, int fd_value);
int		ms_errlog(const char *str, ...);
void	ms_perror(const char *name);
void	ms_waitall(void);
void	leakcheck(const char *str);

#endif
