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
#include "minishell.h"

int	rdrt_append(char **envp, t_rdrt *rdrt)
{
	rdrt->lst_value = expand_arg(envp, rdrt->str_arg);
	if (rdrt_ambiguous(rdrt))
		return (-1);
	return (rdrt_core(rdrt->lst_value->content, STDOUT_FILENO,
			O_CREAT | O_APPEND | O_WRONLY, 0644));
}

int	rdrt_input(char **envp, t_rdrt *rdrt)
{
	rdrt->lst_value = expand_arg(envp, rdrt->str_arg);
	if (rdrt_ambiguous(rdrt))
		return (-1);
	return (rdrt_core(rdrt->lst_value->content, STDIN_FILENO, O_RDONLY));
}

int	rdrt_overwrite(char **envp, t_rdrt *rdrt)
{
	rdrt->lst_value = expand_arg(envp, rdrt->str_arg);
	if (rdrt_ambiguous(rdrt))
		return (-1);
	return (rdrt_core(rdrt->lst_value->content, STDOUT_FILENO,
			O_CREAT | O_TRUNC | O_WRONLY, 0644));
}
