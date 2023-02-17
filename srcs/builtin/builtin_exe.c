#include "minishell.h"
#include "builtin.h"

typedef struct s_builtinlst
{
	const char	*name;
	t_ftbuiltin	ft;
}		t_builtinlst;

// int	ms_isbuiltin(const char *command_expanded, t_data *data)
// {
// 	char						**argv;
// 	int							exe_amt;
// 	static const t_builtinlst	builtinlst[] = {
// 	{"cd", ms_cd},
// 	{"echo", ms_echo},
// 	{"pwd", ms_pwd},
// 	{"export", ms_export},
// 	{"unset", ms_unset},
// 	{"env", ms_env},
// 	{"exit", ctrl_}
// 	};

// 	argv = ms_lexer(command_expanded);
// 	exe_amt = (sizeof(builtinlst) / sizeof(builtinlst[0]));
// 	while (exe_amt--)
// 	{
// 		if (ft_strcmp(argv[0], builtinlst[exe_amt].name))
// 			continue ;
// 		g_lastexit = builtinlst[exe_amt].ft(ft_strcount(argv), argv, data);
// 		ft_strlistclear(argv);
// 		return (1);
// 	}
// 	ft_strlistclear(argv);
// 	return (-1);
// }
