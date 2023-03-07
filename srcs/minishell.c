/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 18:52:48 by hqixeo            #+#    #+#             */
/*   Updated: 2023/03/07 15:22:16 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_common.h"
#include "lexer.h"
#include "parser.h"
#include "executor.h"

void	sig_show(int idunno)
{
	ft_dprintf(2, "sig: %d\n", idunno);
}

void	ms_signals_handler(void)
{
	signal(SIGQUIT, sig_show);
	signal(SIGINT, sig_show);
}

void	ms_interpretor(t_data *data, const char *raw)
{
	t_list	*lst_token;
	t_list	*lst_ctrl;

	lst_token = ms_lexer(raw);
	if (lst_token != NULL && parser_syntax(lst_token) == -1)
		ft_lstclear(&lst_token, del_token);
	if (lst_token == NULL)
		return ;
	lst_ctrl = ms_parser(&lst_token);
	ms_executor(data, &lst_ctrl);
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
			ms_interpretor(&data, input);
		free(input);
	}
	ft_strlistclear(data.envp);
}
