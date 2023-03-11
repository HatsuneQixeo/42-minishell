/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 12:05:17 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/11 23:21:26 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_common.h"
#include <errno.h>

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
