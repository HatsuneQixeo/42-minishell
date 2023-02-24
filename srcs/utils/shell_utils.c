/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_other_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 12:05:17 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/01/09 03:29:34 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isquote(int c)
{
	return (c == '\'' || c == '\"');
}

int	ft_isnameletter(int c)
{
	return (ft_isalnum(c) || c == '_');
}

void	ft_cleanterminal(void)
{
	ft_printf("\e[1;1H\e[2J");
}

void	ms_perror(const char *name)
{
	ms_errlog("");
	perror(name);
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
	else if (fd_attribute == -1 || fd_value == -1)
		return (-1);
	else if (dup2(fd_attribute, fd_value) == -1)
	{
		ft_dprintf(2, "zsh: %s: %s\n", strerror(errno), "dup2");
		ft_dprintf(2, "fd_attribute: %d\n", fd_attribute);
		ft_dprintf(2, "fd_value: %d\n", fd_value);
	}
	else if (close(fd_attribute) == -1)
		ft_dprintf(2, "close error (fd_attribute: %d)\n", fd_attribute);
	else
		return (0);
	return (-1);
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
