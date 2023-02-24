#include "minishell.h"

void	interpretor_core(t_data *data, t_list **lst_ctrl, int infd, int outfd);

/**
 * @brief This function is meant to be the standard execution for executor
 * 
 * Actually, I might as well let them return a pipe?
 * No, this can Overwrite previous pipe setup,
	* there's also no way to return the fd before completing the execution,
	* let's not
 * @param lst_argv 
 * @return pid_t?
 */
int	exe_argv(t_data *data, t_ctrl *exe, int infd, int outfd)
{
	char	**argv;
	t_list	*lst;

	lst = ms_expander(data->envp, exe->lst_args, expand_lst_argv);

	argv = (char **)ft_lsttoaa_clear(&lst);
	ft_strlistiteri(argv, iteristr_showstr);
	ft_strlistclear(argv);
	return (0);
}

/**
 * @brief This function is meant to be the subsh variant
 * Questions:
 * Does the subshell pid matters?
 * 
 * @remark WILL BE ABANDONED, but retained as a value
 * Reason for it is that function template is way too inflexible,
 * unlike pipe, subsh needs to return a readend and writeend
 * 	to the parent process or something like it?
 * 
 * @remark Maybe I complicated things a little bit with pipe and fd
 * Let's try building this without pipe
 * 
 * What should the function returns?
 * 	What even does exe_argv returns anyway?
 * 
 * Where should the executor waits for the exitstatus?
 * 	Until another || && operator?
 * (yes ?)
 * 
 * 
 * @param subsh 
 * @return pid_t?
 */
int	exe_subsh(t_data *data, t_ctrl *subsh, int infd, int outfd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror(MINISHELL"exe_subsh fork");
		return (-1);
	}
	else if (pid == 0)
	{
		interpretor_core(data, &subsh->lst_args, infd, outfd);
		leakcheck("exe_subsh");
		exit(g_lastexit);
	}
	return (pid);
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
}

void	execute_pipe(t_data *data, t_list *lst_exe, int infd, int outfd)
{
	t_ctrl	*ctrl;
	int		prev_read;
	int		*fd_pipe;
	t_list	*lst_pipe;

	prev_read = infd;
	lst_pipe = NULL;
	while (lst_exe->next != NULL)
	{
		fd_pipe = pipe_new();
		ctrl = lst_exe->content;
		ctrl->ft_exe(data, ctrl, prev_read, fd_pipe[WRITE_END]);
		lst_exe = lst_exe->next;
		prev_read = fd_pipe[READ_END];
		ft_lstadd_back(&lst_pipe, ft_lstnew(fd_pipe));
	}
	ctrl = lst_exe->content;
	ctrl->ft_exe(data, ctrl, prev_read, outfd);
	ms_waitall();
	ft_lstclear(&lst_pipe, del_pipe);
}

void	execute(t_data *data, t_list *lst_exe, int infd, int outfd)
{
	t_ctrl	*ctrl;

	ctrl = lst_exe->content;
	if (!ctrl->condition())
		return ;
	else if (lst_exe->next != NULL)
		execute_pipe(data, lst_exe, infd, outfd);
	else
		ctrl->ft_exe(data, lst_exe->content, infd, outfd);
}

t_list	*ft_getlstpipe(t_list **lst_ctrl)
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
void	interpretor_core(t_data *data, t_list **lst_ctrl, int infd, int outfd)
{
	t_list	*lst_exe;

	// ft_printf("interpretor receiving\n");
	// show_lstctrl(*lst_ctrl);
	// ft_printf("interpretor end\n");
	while ((*lst_ctrl) != NULL)
	{
		/* This, this is the point of no return */
		lst_exe = ft_getlstpipe(lst_ctrl);
		// ft_printf("get pipe\n");
		// show_lstctrl(lst_exe);
		// ft_printf("pipe end\n");
		execute(data, lst_exe, infd, outfd);
		/*
			This shouldn't matter in practice?
			In practice the variable would probably be freed in another process
		*/
		// ft_printf("expanded\n");
		// show_lstctrl(lst_exe);
		// ft_printf("expand end\n");
		ft_lstclear(&lst_exe, del_ctrl);
	}
	// ft_printf("interpretor return\n");
}

void	ms_interpretor(t_data *data, t_list **lst_ctrl)
{
	interpretor_core(data, lst_ctrl, 0, 1);
}