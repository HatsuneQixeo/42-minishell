#include "rdrt.h"

static int	ambiguous(const char *token_arg)
{
	ms_errlog("%s: ambiguous redirect\n", token_arg);
	return (-1);
}

static int	rdrt_core(const char *path, int std_fileno, int option, ...)
{
	int		fd;
	va_list	args;

	va_start(args, option);
	fd = open(path, option, va_arg(args, int));
	va_end(args);
	if (fd == -1)
	{
		ms_perror(path);
		return (-1);
	}
	ft_dup3(fd, std_fileno);
	return (0);
}

int	rdrt_heredoc(t_rdrt *rdrt)
{
	/*
		write heredoc
		What if the content is overwritten halfway?
		Shouldn't be possible because I haven't start reading?
		Still need to be aware of fd leaks
	*/
	// return (rdrt_core(rdrt->token_arg, STDIN_FILENO, O_RDONLY));
	return (0);
}

int	rdrt_append(t_rdrt *rdrt)
{
	// if (ft_lstsize(rdrt->lst_value) != 1)
	// 	return (ambiguous(rdrt->token_arg));
	// return (rdrt_core(rdrt->lst_value, STDOUT_FILENO,
	// 	O_CREAT | O_APPEND | O_WRONLY, 0644));
	return (0);
}

int	rdrt_input(t_rdrt *rdrt)
{
	// if (ft_lstsize(rdrt->lst_value) != 1)
	// 	return (ambiguous(rdrt->token_arg));
	// return (rdrt_core(rdrt->lst_value, STDIN_FILENO, O_RDONLY));
	return (0);
}

int	rdrt_overwrite(t_rdrt *rdrt)
{
	// if (ft_lstsize(rdrt->lst_value) != 1)
	// 	return (ambiguous(rdrt->token_arg));
	// return (rdrt_core(rdrt->lst_value, STDOUT_FILENO,
	// 	O_CREAT | O_TRUNC | O_WRONLY, 0644));
	return (0);
}
