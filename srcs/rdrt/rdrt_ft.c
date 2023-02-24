#include "rdrt.h"

int	rdrt_ambiguous(const t_rdrt *rdrt);
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
	rdrt->lst_value = expand_arg(envp, rdrt->str_arg);
	if (rdrt_ambiguous(rdrt))
		return (-1);
	return (rdrt_core(rdrt->lst_value->content, STDOUT_FILENO,
		O_CREAT | O_APPEND | O_WRONLY, 0644));
}

int	rdrt_input(char **envp, t_rdrt *rdrt)
{
	rdrt->lst_value = expand_arg(envp, rdrt->str_arg);
	if (rdrt_ambiguous(rdrt))
		return (-1);
	return (rdrt_core(rdrt->lst_value->content, STDIN_FILENO, O_RDONLY));
}

int	rdrt_overwrite(char **envp, t_rdrt *rdrt)
{
	rdrt->lst_value = expand_arg(envp, rdrt->str_arg);
	if (rdrt_ambiguous(rdrt))
		return (-1);
	return (rdrt_core(rdrt->lst_value->content, STDOUT_FILENO,
		O_CREAT | O_TRUNC | O_WRONLY, 0644));
}
