/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 18:52:48 by hqixeo            #+#    #+#             */
/*   Updated: 2023/03/11 23:21:26 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_common.h"
#include "lexer.h"
#include "parser.h"
#include "executor.h"
#include "signal.h"

int	heretoken(t_token *token_operator, t_token *token_arg)
{
	char	*herestr;

	if (heredoc_limiter(token_arg->value))
		token_operator->value = ft_strmodify(strmod_replace,
				token_operator->value, ft_strdup("\"<<\""));
	herestr = heredoc(token_arg->value);
	if (herestr == NULL)
		return (-1);
	token_arg->value = ft_strmodify(strmod_replace, token_arg->value, herestr);
	return (0);
}

int	ms_heredoc(t_list *lst_token)
{
	t_token	*token;

	while (lst_token != NULL)
	{
		token = lst_token->content;
		lst_token = lst_token->next;
		if (!(token->type == RDRT && rdrt_getft(token->value) == rdrt_heredoc))
			continue ;
		if (heretoken(token, lst_token->content) == -1)
			return (-1);
		lst_token = lst_token->next;
	}
	return (0);
}

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

void	minishell(char **src_envp)
{
	t_data	data;
	char	*input;

	signal(SIGQUIT, SIG_IGN);
	data.envp = ft_strlistdup(src_envp);
	while (1)
	{
		termios_ctrl(TERMHIDE);
		signal(SIGINT, sig_discardline);
		input = readline(MINISHELL"$ ");
		signal(SIGINT, SIG_IGN);
		if (input == NULL)
			break ;
		else if (!stris_only(input, ft_isspace))
			ms_interpretor(&data, input);
		free(input);
	}
	termios_ctrl(TERMSHOW);
	ft_strlistclear(data.envp);
	ft_putendl_fd("exit", 2);
}
