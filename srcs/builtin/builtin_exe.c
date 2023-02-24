#include "builtin.h"

typedef struct s_builtinlst
{
	const char	*name;
	t_ftbuiltin	ft;
}		t_builtinlst[];

int	exec_builtin(char **argv, t_data *data, int infd, int outfd)
{
	int							exe_amt;
	static const t_builtinlst	builtinlst = {
	{"cd", ms_cd},
	{"echo", ms_echo},
	{"pwd", ms_pwd},
	{"export", ms_export},
	{"unset", ms_unset},
	{"env", ms_env},
	{"exit", ms_exit}
	};
	int							fd_stdin;
	int							fd_stdout;

	exe_amt = (sizeof(builtinlst) / sizeof(builtinlst[0]));
	while (exe_amt--)
	{
		if (ft_strcmp(argv[0], builtinlst[exe_amt].name))
			continue ;
		fd_stdin = dup(0);
		fd_stdout = dup(1);
		ft_dup3(infd, 0);
		ft_dup3(outfd, 1);
		g_lastexit = builtinlst[exe_amt].ft(argv, data);
		ft_dup3(fd_stdin, 0);
		ft_dup3(fd_stdout, 1);
		return (0);
	}
	return (-1);
}
