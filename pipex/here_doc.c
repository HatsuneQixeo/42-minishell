/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 08:01:04 by hqixeo            #+#    #+#             */
/*   Updated: 2023/02/25 10:21:05 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

static char	*ft_prompt(const char *prompt)
{
	ft_putstr_fd(prompt, 1);
	return (get_next_line(0));
}

char	*heredoc(const char *limiter_src)
{
	t_list	*lst_buffer;
	char	*limiter;
	char	*input;

	lst_buffer = NULL;
	limiter = ft_strjoin(limiter_src, "\n");
	while (1)
	{
		// Maybe readline in the future?
		input = ft_prompt("heredoc> ");
		if (input == NULL || !ft_strcmp(limiter, input))
			break ;
		ft_lstadd_back(&lst_buffer, ft_lstnew(input));
	}
	free(input);
	free(limiter);
	return (ft_lsttostr_clear(&lst_buffer));
}

static void	write_here_doc(const char *limiter)
{
	int		fd_tmp;
	char	*str;

	str = heredoc(limiter);
	fd_tmp = ft_getfd(HEREDOCTXT, O_RDWR | O_TRUNC | O_CREAT, 0644);
	ft_strrelease_fd(str, fd_tmp);
	close(fd_tmp);
}

void	pipex_here_doc(int argc, char **argv, char **envp)
{
	if (argc < 6)
		return ;
	write_here_doc(argv[2]);
	argv[2] = HEREDOCTXT;
	pipex_core(--argc, ++argv, envp, O_RDWR | O_CREAT | O_APPEND);
	if (ft_strcmp(HEREDOCTXT, argv[argc - 1]))
		unlink(HEREDOCTXT);
}
