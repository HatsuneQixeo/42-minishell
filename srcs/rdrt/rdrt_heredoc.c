/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdrt_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:21:07 by hqixeo            #+#    #+#             */
/*   Updated: 2023/03/16 02:21:41 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "rdrt.h"
#include "expander.h"

static int	write_here_doc(const char *content)
{
	int	fd_here;

	fd_here = open(HEREDOC_TXT, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd_here == -1)
	{
		ms_perror(HEREDOC_TXT);
		return (-1);
	}
	ft_putendl_fd(content, fd_here);
	close(fd_here);
	return (0);
}

int	rdrt_heredoc(char **envp, t_rdrt *rdrt)
{
	rdrt->str_arg = ft_strmodify(strmod_replace,
			rdrt->str_arg, simpleexpand(envp, rdrt->str_arg));
	return (rdrt_quotedheredoc(envp, rdrt));
}

int	rdrt_quotedheredoc(char **envp, t_rdrt *rdrt)
{
	if (write_here_doc(rdrt->str_arg) == -1)
		return (-1);
	return (rdrt_core(HEREDOC_TXT, STDIN_FILENO, O_RDONLY));
	(void)envp;
}
