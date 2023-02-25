/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdrt_ftcore.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:21:07 by hqixeo            #+#    #+#             */
/*   Updated: 2023/02/25 10:21:07 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_common.h"

int	stris_onlyspace(const char *str)
{
	while (*str != '\0' && ft_isspace(*str))
		str++;
	return (*str == '\0');
}

int	rdrt_ambiguous(const t_list *lst_value, const char *str_arg)
{
	if (lst_value == NULL || lst_value->next != NULL
		|| stris_onlyspace(lst_value->content))
		ms_errlog("%s: ambiguous redirect\n", str_arg);
	else
		return (0);
	return (1);
}

int	rdrt_core(const char *path, int std_fd, int option, ...)
{
	int		fd;
	va_list	args;

	va_start(args, option);
	fd = open(path, option, va_arg(args, int));
	va_end(args);
	if (fd == -1)
	{
		ms_perror(path);
		return (-1);
	}
	return (ft_dup3(fd, std_fd));
}
