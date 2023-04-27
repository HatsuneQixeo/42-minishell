/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 18:52:48 by hqixeo            #+#    #+#             */
/*   Updated: 2023/03/16 02:21:41 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ms_common.h"
#include "lexer.h"
#include "parser.h"
#include "executor.h"
#include "signal.h"

static void	ms_interpretor(t_data *data, const char *raw)
{
	t_list	*lst_token;
	t_list	*lst_ctrl;

	lst_token = ms_lexer(raw);
	if (lst_token != NULL
		&& (parser_syntax(lst_token) == -1 || ms_heredoc(lst_token) == -1))
		ft_lstclear(&lst_token, del_token);
	if (lst_token == NULL)
		return ;
	lst_ctrl = ms_parser(&lst_token);
	ms_executor(data, &lst_ctrl);
	leakcheck("interpretor end");
	leakfd("interpretor end");
}

char	*prompt_std(void)
{
	return (readline(MINISHELL"$ "));
}

char	*prompt_silent(void)
{
	return (ft_prompt(""));
}

typedef char	*(*t_prompt)(void);

void	minishell(t_data *data)
{
	const t_prompt	ft_read = (t_prompt []){
		prompt_silent,
		prompt_std
	}[isatty(0)];
	char			*input;

	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		termios_ctrl(TERMHIDE);
		signal(SIGINT, sig_discardline);
		input = ft_read();
		signal(SIGINT, SIG_IGN);
		if (input == NULL)
			break ;
		else if (input[0] != '\0' && !(data->isscript && input[0] == '#'))
			ms_interpretor(data, input);
		free(input);
	}
	termios_ctrl(TERMSHOW);
	if (isatty(1) && isatty(0))
		ft_putendl_fd("exit", 2);
	leakcheck("Main end");
	exit(g_lastexit);
}
