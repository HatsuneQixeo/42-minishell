/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:21:07 by hqixeo            #+#    #+#             */
/*   Updated: 2023/03/07 15:22:17 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rdrt.h"
#include "expander.h"

static int	write_here_doc(t_list *lst_value)
{
	int	fd_here;

	fd_here = open(HEREDOC_TXT, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (fd_here == -1)
	{
		ms_perror(HEREDOC_TXT);
		return (-1);
	}
	while (lst_value != NULL)
	{
		ft_putendl_fd(lst_value->content, fd_here);
		lst_value = lst_value->next;
	}
	close(fd_here);
	return (0);
}

int	rdrt_heredoc(char **envp, t_rdrt *rdrt)
{
	heredoc_expand(envp, rdrt->lst_value);
	return (rdrt_quotedheredoc(envp, rdrt));
}

int	rdrt_quotedheredoc(char **envp, t_rdrt *rdrt)
{
	if (write_here_doc(rdrt->lst_value) == -1)
		return (-1);
	return (rdrt_core(HEREDOC_TXT, STDIN_FILENO, O_RDONLY));
	(void)envp;
}
