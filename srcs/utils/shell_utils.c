/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 12:05:17 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/02/25 10:21:07 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_common.h"

int	ft_isquote(int c)
{
	return (c == '\'' || c == '\"');
}

int	ft_isnameletter(int c)
{
	return (ft_isalnum(c) || c == '_');
}

int	ms_errlog(const char *str_format, ...)
{
	va_list	args;
	int		ret;

	va_start(args, str_format);
	ret = ft_putstr_fd(MINISHELL": ", 2) + ft_printf_core(2, str_format, args);
	va_end(args);
	return (ret);
}

void	ms_perror(const char *name)
{
	ms_errlog("%s: %s\n", name, strerror(errno));
}

/**
 * @brief Closes the original fd, essentially function as replacing the fd.
 * @note Does not do anything if the fd_attribute is the same as ft_value
 * @param fd_attribute The attribute of the file descriptor
 * @param fd_value The value of the file descriptor
 * 
 * @return int -1 if either fd is -1, or either dup2 or close failed,
 * 	0 by default
 */
int	ft_dup3(int fd_attribute, int fd_value)
{
	if (fd_attribute == fd_value)
		return (0);
	else if (fd_attribute == -1)
		ft_dprintf(2, "fd_attribute: %d\n", fd_attribute);
	else if (fd_value == -1)
		ft_dprintf(2, "fd_value: %d\n", fd_value);
	else if (dup2(fd_attribute, fd_value) == -1)
	{
		ms_perror("dup2");
		ft_dprintf(2, "fd_attribute: %d\n", fd_attribute);
		ft_dprintf(2, "fd_value: %d\n", fd_value);
	}
	else if (close(fd_attribute) == -1)
		ft_dprintf(2, "close error (fd_attribute: %d)\n", fd_attribute);
	else
		return (0);
	return (-1);
}
