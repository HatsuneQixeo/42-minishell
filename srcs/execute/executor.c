/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:21:06 by hqixeo            #+#    #+#             */
/*   Updated: 2023/02/25 10:21:06 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	redirection(char **envp, t_list *lst_rdrt)
{
	t_rdrt	*rdrt;

	if (lst_rdrt == NULL)
		return (0);
	while (lst_rdrt != NULL)
	{
		rdrt = lst_rdrt->content;
		if (rdrt->ft_rdrt(envp, rdrt) == -1)
			return (-1);
		lst_rdrt = lst_rdrt->next;
	}
	return (0);
}

int	exe_argv(t_data *data, t_ctrl *exe)
{
	char	**argv;
	t_list	*lst;

	if (exe->lst_args == NULL)
		return (0);
	if (redirection(data->envp, exe->lst_rdrt) == -1)
		return (-1);
	lst = ms_expander(data->envp, exe->lst_args, expand_lst_argv);
	argv = (char **)ft_lsttoaa_clear(&lst);
	g_lastexit = execution(data, argv);
	ft_strlistclear(argv);
	dup2(data->fd_std[0], 0);
	dup2(data->fd_std[1], 1);
	unlink(HEREDOC_TXT);
	return (0);
}

int	exe_subsh(t_data *data, t_ctrl *subsh)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror(MINISHELL"exe_subsh fork");
		return (-1);
	}
	else if (pid == 0)
	{
		ms_interpretor(data, &subsh->lst_args);
		leakcheck("exe_subsh");
		exit(g_lastexit);
	}
	else
		waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}

int	*pipe_new(void)
{
	int	*newpipe;

	newpipe = malloc(2 * sizeof(int));
	if (newpipe != NULL && pipe(newpipe) != -1)
		return (newpipe);
	free(newpipe);
	perror(MINISHELL": pipe_new");
	return (NULL);
}

void	del_pipe(void *content)
{
	int	*fd_pipe;

	fd_pipe = content;
	if (close(fd_pipe[READ_END]) == -1)
		perror("del READ_END");
	if (close(fd_pipe[WRITE_END]) == -1)
		perror("del WRITE_END");
	free(fd_pipe);
}

// void	execute_pipe(t_data *data, t_list *lst_exe)
// {
// 	t_ctrl	*ctrl;
// 	int		prev_read;
// 	int		*fd_pipe;
// 	t_list	*lst_pipe;

// 	prev_read = infd;
// 	lst_pipe = NULL;
// 	while (lst_exe->next != NULL)
// 	{
// 		fd_pipe = pipe_new();
// 		ctrl = lst_exe->content;
// 		ctrl->ft_exe(data, ctrl, prev_read, fd_pipe[WRITE_END]);
// 		lst_exe = lst_exe->next;
// 		prev_read = fd_pipe[READ_END];
// 		ft_lstadd_back(&lst_pipe, ft_lstnew(fd_pipe));
// 	}
// 	ctrl = lst_exe->content;
// 	ctrl->ft_exe(data, ctrl, prev_read, outfd);
// 	ms_waitall();
// 	ft_lstclear(&lst_pipe, del_pipe);
// }

void	interpretion(t_data *data, t_list *lst_exe)
{
	t_ctrl	*ctrl;

	ctrl = lst_exe->content;
	if (!ctrl->condition())
		return ;
	// else if (lst_exe->next != NULL)
	// 	execute_pipe(data, lst_exe);
	ctrl->ft_exe(data, lst_exe->content);
}

t_list	*inptr_getlstpipe(t_list **lst_ctrl)
{
	t_list	*lst_exe;
	t_ctrl	*ctrl;

	lst_exe = ft_lstextract_front(lst_ctrl);
	while ((*lst_ctrl) != NULL)
	{
		ctrl = (*lst_ctrl)->content;
		if (ctrl->condition != ctrl_continue)
			break ;
		ft_lstadd_back(&lst_exe, ft_lstextract_front(lst_ctrl));
	}
	return (lst_exe);
}

/**
 * @brief (echo $MIKU && (echo is && echo cute) || echo $MIKU is cute) | tr [:lower:] [:upper:]
 * echo $MIKU | (echo cat1 && cat && (echo cat2 && cat))
 * 
 * @param envp 
 * @param lst_ctrl 
 */
void	ms_interpretor(t_data *data, t_list **lst_ctrl)
{
	t_list	*lst_exe;

	while ((*lst_ctrl) != NULL)
	{
		lst_exe = inptr_getlstpipe(lst_ctrl);
		interpretion(data, lst_exe);
		ft_lstclear(&lst_exe, del_ctrl);
	}
}
