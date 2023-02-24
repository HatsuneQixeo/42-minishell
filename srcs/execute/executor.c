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
int	exe_argv(t_data *data, t_list *lst_argv, int infd, int outfd)
{
	char	**argv;
	t_list	*lst;

	lst = ms_expander(data->envp, lst_argv, expand_lst_argv);
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
 * (yes)
 * 
 * 
 * @param subsh 
 * @return pid_t?
 */
int	exe_subsh(t_data *data, t_list *lst_ctrl, int infd, int outfd)
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
		interpretor_core(data, &lst_ctrl, infd, outfd);
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

void	execute(t_data *data, t_list *lst_pipe, int infd, int outfd)
{
	t_ctrl	*ctrl;
	/* Lst of pipes */

	while (lst_pipe != NULL)
	{
		ctrl = lst_pipe->content;
		ctrl->ft_exe(data, ctrl->lst_exe, infd/* ?? */, outfd/* ?? */);
		lst_pipe = lst_pipe->next;
	}
}

t_list	*ft_getlstpipe(t_list **lst_ctrl)
{
	t_list	*lst_pipe;
	t_ctrl	*ctrl;

	lst_pipe = ft_lstextract_front(lst_ctrl);
	while ((*lst_ctrl) != NULL)
	{
		ctrl = (*lst_ctrl)->content;
		if (ctrl->condition != ctrl_continue)
			break ;
		ft_lstadd_back(&lst_pipe, ft_lstextract_front(lst_ctrl));
	}
	return (lst_pipe);
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
	t_list	*lst_pipe;

	// ft_printf("interpretor receiving\n");
	// show_lstctrl(*lst_ctrl);
	// ft_printf("interpretor end\n");
	while ((*lst_ctrl) != NULL)
	{
		/* This, this is the point of no return */
		lst_pipe = ft_getlstpipe(lst_ctrl);
		// ft_printf("get pipe\n");
		// show_lstctrl(lst_pipe);
		// ft_printf("pipe end\n");
		execute(data, lst_pipe, infd, outfd);
		/*
			This shouldn't matter in practice?
			In practice the variable would probably be freed in another process
		*/
		// ft_printf("expanded\n");
		// show_lstctrl(lst_pipe);
		// ft_printf("expand end\n");
		ft_lstclear(&lst_pipe, del_ctrl);
	}
	// ft_printf("interpretor return\n");
}

void	ms_interpretor(t_data *data, t_list **lst_ctrl)
{
	show_lstctrl(*lst_ctrl);
	interpretor_core(data, lst_ctrl, 0, 1);
	leakcheck("interpretor end");
}