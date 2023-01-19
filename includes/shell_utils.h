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

int		ft_isnameletter(int c);
void	ft_clear_screen(void);
size_t	shell_varname_len(const char *input);
void	shell_backslash(char *str);
void	ms_pathaccess(char **executable);
#endif