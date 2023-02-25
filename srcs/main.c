/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 12:10:40 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/02/25 18:26:23 by hqixeo           ###   ########.fr       */
/*                                                                           */
/* ************************************************************************** */

#include "minishell.h"

#ifndef SAN
# define SAN	0
#endif

void	leakcheck(const char *str)
{
	char	buffer[39];

	if (SAN != 0)
		return ;
	ft_printf("\nleakcheck: %s\n", str);
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

int	main(int argc, char **argv, char **envp)
{
	ft_printf("\e[1;1H\e[2J");
	ms_signals_handler();
	minishell(envp);
	leakcheck("mainend");
	(void)argc;
	(void)argv;
}
