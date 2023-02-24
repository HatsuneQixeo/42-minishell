#include "rdrt.h"

int	ambiguous(const char *str_arg);
int	rdrt_core(const char *path, int std_fileno, int option, ...);

int	rdrt_heredoc(char **envp, t_rdrt *rdrt)
{
	/*
		write heredoc
		What if the content is overwritten halfway?
		Shouldn't be possible because I haven't start reading?
		Still need to be aware of fd leaks
	*/
	// return (rdrt_core(rdrt->str_arg, STDIN_FILENO, O_RDONLY));
	return (0);
}

int	rdrt_quotedheredoc(char **envp, t_rdrt *rdrt)
{
	/*
		write heredoc
		What if the content is overwritten halfway?
		Shouldn't be possible because I haven't start reading?
		Still need to be aware of fd leaks
	*/
	// return (rdrt_core(rdrt->str_arg, STDIN_FILENO, O_RDONLY));
	return (0);
}

int	rdrt_append(char **envp, t_rdrt *rdrt)
{
	// if (ft_lstsize(rdrt->lst_value) != 1)
	// 	return (ambiguous(rdrt->str_arg));
	// return (rdrt_core(rdrt->lst_value, STDOUT_FILENO,
	// 	O_CREAT | O_APPEND | O_WRONLY, 0644));
	return (0);
}

int	rdrt_input(char **envp, t_rdrt *rdrt)
{
	// if (ft_lstsize(rdrt->lst_value) != 1)
	// 	return (ambiguous(rdrt->str_arg));
	// return (rdrt_core(rdrt->lst_value, STDIN_FILENO, O_RDONLY));
	return (0);
}

int	rdrt_overwrite(char **envp, t_rdrt *rdrt)
{
	// if (ft_lstsize(rdrt->lst_value) != 1)
	// 	return (ambiguous(rdrt->str_arg));
	// return (rdrt_core(rdrt->lst_value, STDOUT_FILENO,
	// 	O_CREAT | O_TRUNC | O_WRONLY, 0644));
	return (0);
}
