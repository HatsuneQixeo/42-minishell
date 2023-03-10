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
#include "signal.h"

// t_rdrt	*parse_rdrt_new(t_token *token_rdrt, t_token *token_arg)
// {
// 	t_rdrt	*rdrt;

// 	rdrt = rdrt_new(rdrt_getft(token_rdrt->value), token_arg->value);
// 	if (rdrt->ft_rdrt == rdrt_heredoc)
// 	{
// 		if (heredoc_limiter(rdrt->str_arg))
// 			rdrt->ft_rdrt = rdrt_quotedheredoc;
// 		rdrt->lst_value = heredoc(rdrt->str_arg);
// 	}
// 	return (rdrt);
// }

// void	ms_heredoc(t_list *lst_token)
// {
// 	t_token	*token;

// 	while (lst_token != NULL)
// 	{
// 		token = lst_token->content;
// 		lst_token = lst_token->next;
// 		if (!(token->type == RDRT && rdrt_getft(token->value) != rdrt_heredoc))
// 			continue ;
// 		t_token	*token_arg;
// 		token_arg = lst_token->content;
// 		if (heredoc_limiter(token_arg->value))
// 			token->value = ft_strmodify(strmod_replace,
// 				token->value, ft_strdup("\"<<\""));
// 		rdrt->lst_value = heredoc(token_arg->value);
// 		lst_token = lst_token->next;
// 	}
// }

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
	// show_lstctrl(lst_ctrl);
	ms_executor(data, &lst_ctrl);
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
		mssig_readline();
		input = readline(MINISHELL"$ ");
		if (input == NULL)
			break ;
		else if (!stris_only(input, ft_isspace))
			ms_interpretor(&data, input);
		free(input);
	}
	ft_strlistclear(data.envp);
	ft_putendl_fd("exit", 2);
}
