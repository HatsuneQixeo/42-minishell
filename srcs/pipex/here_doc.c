/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 08:01:04 by hqixeo            #+#    #+#             */
/*   Updated: 2022/11/13 08:01:06 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

static char	*heredoc_prompt(int pipec)
{
	while (pipec--)
		ft_printf("pipe ");
	ft_printf("heredoc> ");
	return (get_next_line(0));
}

static char	*right_here_right_now(int argc, const char *limiter_src)
{
	char	*buffer;
	char	*limiter;
	char	*input;

	buffer = NULL;
	limiter = ft_strjoin(limiter_src, "\n");
	input = heredoc_prompt(argc - 5);
	while (input != NULL && ft_strcmp(limiter, input))
	{
		buffer = ft_strcombine(buffer, input);
		input = heredoc_prompt(argc - 5);
	}
	free(input);
	free(limiter);
	return (buffer);
}

void	pipex_here_doc(int argc, char **argv, char **envp)
{
	int		fd_tmp;
	char	*str;

	if (argc < 6)
		return ;
	str = right_here_right_now(argc, argv[2]);
	fd_tmp = ft_getfd(HEREDOC, O_RDWR | O_TRUNC | O_CREAT, 0644);
	ft_strrelease_fd(str, fd_tmp);
	close(fd_tmp);
	argv[2] = HEREDOC;
	pipex_core(--argc, ++argv, envp, O_RDWR | O_CREAT | O_APPEND);
	if (ft_strcmp(HEREDOC, argv[argc - 1]))
		unlink(HEREDOC);
}
