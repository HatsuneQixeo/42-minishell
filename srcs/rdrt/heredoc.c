/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:21:07 by hqixeo            #+#    #+#             */
/*   Updated: 2023/02/25 10:21:07 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rdrt.h"
#include "expander.h"

static char	*heredoc_expand_line(char **envp, const char *str)
{
	t_list		*lst_expanded;
	const char	*ptr_var;

	lst_expanded = NULL;
	while (1)
	{
		ptr_var = ft_strchr(str, '$');
		if (ptr_var == NULL)
			break ;
		ft_lstadd_back(&lst_expanded, ft_lstnew(
				ft_substr(str, 0, ptr_var - str)));
		ft_lstadd_back(&lst_expanded, ft_lstnew(
				expand_var(envp, &ptr_var)));
		str = ptr_var + 1;
	}
	ft_lstadd_back(&lst_expanded, ft_lstnew(ft_strdup(str)));
	return (ft_lsttostr_clear(&lst_expanded));
}

static void	heredoc_expand(char **envp, t_list *lst)
{
	char	*tmp;

	while (lst != NULL)
	{
		tmp = lst->content;
		lst->content = heredoc_expand_line(envp, lst->content);
		free(tmp);
		lst = lst->next;
	}
}

static int	write_here_doc(t_list *lst_value)
{
	int	fd_here;

	fd_here = open(HEREDOC_TXT, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (fd_here == -1)
	{
		ms_perror(HEREDOC_TXT);
		return (-1);
	}
	ft_strrelease_fd(ft_lsttostr_delimiter(lst_value, "\n"), fd_here);
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
