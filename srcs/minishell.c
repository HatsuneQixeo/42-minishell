#include "ms_common.h"
#include "parser.h"
#include "interpretor.h"

/* routine */
char	*ms_closequote(const char *raw);
/* Lexer */
t_list	*ms_lexer(const char *input_raw);

#ifndef SAN
# define SAN	0
#endif

void	leakcheck(const char *str)
{
	char	buffer[39];

	if (SAN)
		return ;
	ft_dprintf(2, "\nleakcheck: %s\n", str);
	snprintf(buffer, sizeof(buffer), "leaks -q %d >&2", getpid());
	system(buffer);
}

void	leakfd(const char *str)
{
	int	arr[100];
	int	fd_expect;

	ft_dprintf(2, "\nleakfd: %s\n", str);
	fd_expect = 3;
	for (int i = 0; i < 100 && fd_expect < 1024 && fd_expect != -1; i++)
	{
		arr[i] = open("minishell", O_RDONLY);
		if (arr[i] != fd_expect)
			ft_dprintf(2, "fdleak: %d-%d\n", fd_expect, arr[i] - 1);
		fd_expect = arr[i] + 1;
	}
	for (int i = 0; i < 100; i++)
		close(arr[i]);
}

void	ms_signals_handler(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
}

void	ms_procedure(t_data *data, const char *raw)
{
	char	*input;

	input = ms_closequote(raw);
	if (input == NULL)
		return ;
	add_history(input);
	t_list	*lst = ms_lexer(input);
	free(input);

	if (parser_syntax(lst) == -1)
	{
		ft_lstclear(&lst, del_token);
		return ;
	}
	t_list	*lst_ctrl = ms_parser(&lst);

	// show_lstctrl(lst_ctrl);
	ms_interpretor(data, &lst_ctrl);
	leakcheck("interpretor end");
	leakfd("interpretor end");
}

void	minishell(char **src_envp)
{
	t_data	data;
	char	*input;

	data.envp = ft_strlistdup(src_envp);
	ms_signals_handler();
	while (1)
	{
		input = readline(MINISHELL"$ ");
		if (input == NULL)
			break ;
		else if (!stris_only(input, ft_isspace))
			ms_procedure(&data, input);
		free(input);
	}
	ft_strlistclear(data.envp);
}
