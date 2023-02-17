#include "minishell.h"

/**
 * @brief An executor that always assume it's in the main process?
 * (exit) Does not exit the program because this is ran in subshell, fork it
 */
void	ms_wait(void)
{
	int	status;

	while (wait(&status) != -1)
		g_lastexit = WEXITSTATUS(status);
}

void	*lstmap_defaulttoken(void *value)
{
	return (token_new(value, DEFAULT));
}

/**
 * @brief Still have to retain the original format because it's token
 * 	Dont run this just yet, will leaks like washing machine
 * @param lst_argv A linked list of 
 * @return t_list* A list of tokens, where it's properly parsed as bash would
 */
t_list	*exe_expand_lst_argv(char **envp, t_list *lst_argv)
{
	t_list	*lst_new;
	t_list	*it;

	it = lst_argv;
	while (it != NULL)
	{
		t_token	*token = it->content;

		/* This condition might not be necessary later on
			after I finish excluding the ctrl and subsh token,
			how pipe tho? */
		/* No, subsh only, ctrl shouldn't be in argv layer */
		if (token->type != DEFAULT && !isoperator_rdrt(token->type))
		{
			it = it->next;
			continue ;
		}
		/* No, this is not token, just a list of strings */
		t_list	*lst_expanded_args = ms_expand_arg(envp, token->value);

		if (token->type == DEFAULT)
		{
			ft_lstadd_back(&lst_new, ft_lstmap(
				lst_expanded_args, lstmap_defaulttoken, del_token));
		}
		else if (lst_expanded_args == NULL || ft_lstsize(lst_expanded_args) > 1)
		{
			ft_dprintf(2, MINISHELL": %s: ambiguous redirect\n", token->value);
			ft_lstclear(&lst_expanded_args, free);
			ft_lstclear(&lst_new, del_token);
			return (NULL);
		}
		else
			ft_lstadd_back(&lst_new, ft_lstnew(
				token_new(lst_expanded_args->content, token->type)));
		ft_lstclear(&lst_expanded_args, free);
		it = it->next;
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
	int		pipex[2];

	if (pipe(pipex) == -1)
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
		close(pipex[READ_END]);
		// Am i duping the right fd?
		ft_dup3(pipex[WRITE_END], STDOUT_FILENO);
		/* This return the content in a pipe readend fd,
			how can I return this in child? */
		/* Hey, recursive subsh?
			This should be calling whoever is calling this function,
			recursively */
		// exe_argv(lst_ctrl); // ? next
		// What is this child suppose to exit
		exit(g_lastexit);
	}
	else
		close(pipex[WRITE_END]);
	/* This function return the read_end before the execution is complete.
		So theorically this should be able to connect pipe */
	return (pipex[READ_END]); // ? read and? how connect?
}
