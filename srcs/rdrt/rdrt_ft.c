/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdrt_ft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:21:07 by hqixeo            #+#    #+#             */
/*   Updated: 2023/03/16 02:21:41 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "rdrt.h"

static int	rdrt_ambiguousfilename(const t_list *lst_value, const char *str_arg)
{
	const char	*reason;

	if (lst_value == NULL)
		reason = "Invalid variable";
	else if (lst_value->next != NULL)
		reason = "Unquoted space";
	else
		return (0);
	ms_errlog("%s: ambiguous redirect: %s\n", str_arg, reason);
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
		ms_perror(path);
	else
		return (ft_dup3(fd, std_fd));
	return (-1);
}

int	rdrt_append(char **envp, t_rdrt *rdrt)
{
	rdrt->lst_value = expand_arg(envp, rdrt->str_arg);
	if (rdrt_ambiguousfilename(rdrt->lst_value, rdrt->str_arg))
		return (-1);
	return (rdrt_core(rdrt->lst_value->content, STDOUT_FILENO,
			O_CREAT | O_APPEND | O_WRONLY, 0644));
}

int	rdrt_input(char **envp, t_rdrt *rdrt)
{
	rdrt->lst_value = expand_arg(envp, rdrt->str_arg);
	if (rdrt_ambiguousfilename(rdrt->lst_value, rdrt->str_arg))
		return (-1);
	return (rdrt_core(rdrt->lst_value->content, STDIN_FILENO, O_RDONLY));
}

int	rdrt_overwrite(char **envp, t_rdrt *rdrt)
{
	rdrt->lst_value = expand_arg(envp, rdrt->str_arg);
	if (rdrt_ambiguousfilename(rdrt->lst_value, rdrt->str_arg))
		return (-1);
	return (rdrt_core(rdrt->lst_value->content, STDOUT_FILENO,
			O_CREAT | O_TRUNC | O_WRONLY, 0644));
}
