#include "minishell.h"
#define ERR	((void *)-1)

void	*lstmap_str_to_def_token(void *value)
{
	return (token_new(value, DEFAULT));
}

t_list	*expand_lstmap_rdrt(char **envp, t_token *token)
{
	static int	isheredoc;
	t_list		*lst_args;

	if (isheredoc)
	{
		isheredoc = 0;
		return (ft_lstnew(token_new(ft_strdup(token->value), DEFAULT)));
	}
	else if (!ft_strcmp(token->value, "<<"))
		isheredoc = 1;
	if (isoperator_rdrt(token->type))
		return (ft_lstnew(token_new(ft_strdup(token->value), RDRT)));
	lst_args = ms_expander(envp, token->value);
	debuglst_tmpname(lst_args, lstiter_strname, "rdrt", lstiter_showstr);
	if (ft_lstsize(lst_args) == 1)
	{
		lst_args->content = token_new(lst_args->content, DEFAULT);
		return (lst_args);
	}
	ft_dprintf(2, MINISHELL": %s: ambiguous redirect\n", token->value);
	ft_lstclear(&lst_args, free);
	return (ERR);
}

t_list	*expand_lstmap_argv(char **envp, t_token *token)
{
	t_list	*lst_expanded_args;
	t_list	*lst_mapped_token;

	lst_expanded_args = ms_expander(envp, token->value);
	lst_mapped_token = ft_lstmap(lst_expanded_args, lstmap_str_to_def_token, del_token);
	ft_lstclear(&lst_expanded_args, NULL);
	return (lst_mapped_token);
}

typedef t_list	*(t_ftexpand)(char **envp, t_token *token);

t_list	*exe_expand_lst(char **envp, t_list *lst, t_ftexpand ft_expand)
{
	t_list	*lst_new;
	t_list	*ret;

	lst_new = NULL;
	while (lst != NULL)
	{
		ret = ft_expand(envp, lst->content);
		if (ret == ERR)
		{
			ft_lstclear(&lst_new, del_token);
			return (NULL);
		}
		ft_lstadd_back(&lst_new, ret);
		lst = lst->next;
	}
	return (lst_new);
}

/**
 * @brief This function is meant to be the standard execution for executor
 * 
 * Actually, I might as well let them return a pipe?
 * No, this can Overwrite previous pipe setup,
	* there's also no way to return the fd before completing the execution,
	* let's not
 * Imagine not having envp for execve
 * @param lst_argv 
 * @return int ?????
 */
int	exe_argv(char **envp, t_list *lst_argv, int fd_in, int fd_out)
{
	/* Note, the given lst is still a lst of tokens */
	char	**argv;

	// argv = ;
	// Convert to char ** for execve
	// if ()
	(void)argv;
	return (0);
}

/**
 * @brief This function is meant to be the subsh variant
 * Questions:
 * Does the subshell pid matters?
 * 
 * What should the function returns?
 * 	fd_read? ain't that confusing with exe_argv?
 * 	What even does exe_argv returns anyway?
 * 
 * Where should the executor waits for the exitstatus?
 * 	Until another || && operator?
 * 
 * 
 * @param subsh 
 * @return int 
 */
int	exe_subsh(char **envp, t_list *lst_ctrl, int fd_in, int fd_out)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
	{
		perror(MINISHELL"exe_subsh pipe");
		return (-1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror(MINISHELL"exe_subsh fork");
		return (-1);
	}
	else if (pid == 0)
	{
		close(pipefd[READ_END]);
		/* Am i duping the right fd? */
		ft_dup3(pipefd[WRITE_END], STDOUT_FILENO);
		/* This return the content in a pipe readend fd,
			how can I return this in child? */
		/* Hey, recursive subsh?
			This should be calling whoever is calling this function,
			recursively */
		ms_interpretor(envp, lst_ctrl->content);
		/* What is this child suppose to exit,
			I guess exit(g_lastexit) makes it retain the exit value */
		exit(g_lastexit);
	}
	else
		close(pipefd[WRITE_END]);
	/* This function return the read_end before the execution is complete.
		So theorically this should be able to connect pipe */
	return (pipefd[READ_END]); // ? read and? how connect?
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

/* Currently only expanding */
void	execute(char **envp, t_list *lst_pipe)
{
	ft_printf("execute\n");
	while (lst_pipe != NULL)
	{
		t_ctrl	*ctrl = lst_pipe->content;
		t_list	*new;

		if (ctrl->ft_exe == exe_argv)
		{
			new = exe_expand_lst(envp, ctrl->lst_exe, expand_lstmap_argv);
			ft_lstclear(&ctrl->lst_exe, del_token);
			ctrl->lst_exe = new;
		}
		else
			ms_interpretor(envp, &ctrl->lst_exe);
		if (ctrl->lst_rdrt != NULL)
		{
			new = exe_expand_lst(envp, ctrl->lst_rdrt, expand_lstmap_rdrt);
			if (new == NULL)
				return ;
			ft_lstclear(&ctrl->lst_rdrt, del_token);
			ctrl->lst_rdrt = new;
		}
		lst_pipe = lst_pipe->next;
	}
}

/**
 * @brief (echo $MIKU && (echo is && echo cute) || echo $MIKU is cute) | tr [:lower:] [:upper:]
 * 
 * @param envp 
 * @param lst_ctrl 
 */
void	ms_interpretor(char **envp, t_list **lst_ctrl)
{
	t_list	*lst_pipe;

	ft_printf("interpretor receiving\n");
	show_lstctrl(*lst_ctrl);
	ft_printf("interpretor end\n");
	while ((*lst_ctrl) != NULL)
	{
		lst_pipe = ft_getlstpipe(lst_ctrl);
		ft_printf("get pipe\n");
		show_lstctrl(lst_pipe);
		ft_printf("pipe end\n");
		execute(envp, lst_pipe);
		ft_printf("expanded\n");
		show_lstctrl(lst_pipe);
		ft_printf("expand end\n");
		ft_lstclear(&lst_pipe, del_ctrl);
	}
	ft_printf("interpretor return\n");
}