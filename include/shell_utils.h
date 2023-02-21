/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 00:52:27 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/01/09 03:27:24 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_UTILS_H
# define SHELL_UTILS_H

# include <unistd.h>
# include <stdlib.h>

# include "libft.h"

int		ft_isquote(int c);
int		ft_isnameletter(int c);
void	ft_cleanterminal(void);
void	ms_perror(const char *name);
char	closing_quote(const char *it);
void	ms_waitall(void);

#endif