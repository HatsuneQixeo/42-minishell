/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdrt_ft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:21:07 by hqixeo            #+#    #+#             */
/*   Updated: 2023/02/25 10:21:07 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rdrt.h"

int	rdrt_ambiguous(const t_list *lst_value, const char *str_arg)
{
	/* Need some more experiment and modification with expander to deal with this */
	if (lst_value == NULL || lst_value->next != NULL
		|| stris_only(lst_value->content, ft_isspace))
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

int	rdrt_append(char **envp, t_rdrt *rdrt)
{
	rdrt->lst_value = expand_arg(envp, rdrt->str_arg);
	if (rdrt_ambiguous(rdrt->lst_value, rdrt->str_arg))
		return (-1);
	return (rdrt_core(rdrt->lst_value->content, STDOUT_FILENO,
			O_CREAT | O_APPEND | O_WRONLY, 0644));
}

int	rdrt_input(char **envp, t_rdrt *rdrt)
{
	rdrt->lst_value = expand_arg(envp, rdrt->str_arg);
	if (rdrt_ambiguous(rdrt->lst_value, rdrt->str_arg))
		return (-1);
	return (rdrt_core(rdrt->lst_value->content, STDIN_FILENO, O_RDONLY));
}

int	rdrt_overwrite(char **envp, t_rdrt *rdrt)
{
	rdrt->lst_value = expand_arg(envp, rdrt->str_arg);
	if (rdrt_ambiguous(rdrt->lst_value, rdrt->str_arg))
		return (-1);
	return (rdrt_core(rdrt->lst_value->content, STDOUT_FILENO,
			O_CREAT | O_TRUNC | O_WRONLY, 0644));
}
