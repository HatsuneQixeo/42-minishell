/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 12:16:10 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/02/27 16:12:50 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_rdrt	*parser_rdrt_new(t_list *node_rdrt, t_list *node_arg)
{
	t_token	*token_rdrt;
	t_token	*token_arg;
	t_rdrt	*rdrt;

	token_rdrt = node_rdrt->content;
	token_arg = node_arg->content;
	rdrt = rdrt_new(rdrt_getft(token_rdrt->value), token_arg->value);
	ft_lstdelone(node_rdrt, del_token);
	ft_lstdelone(node_arg, free);
	if (rdrt->ft_rdrt == rdrt_heredoc)
	{
		if (heredoc_limiter(rdrt->str_arg))
			rdrt->ft_rdrt = rdrt_quotedheredoc;
		rdrt->lst_value = heredoc(rdrt->str_arg);
	}
	return (rdrt);
}

static t_ctrl	*parser_ctrlnode(t_list **lst_token, t_ftctrl *condition)
{
	t_ctrl	*ctrl;
	t_list	*node_token;
	t_token	*token;

	ctrl = ctrl_new(*condition, exe_argv, del_token);
	while (*lst_token != NULL)
	{
		node_token = ft_lstextract_front(lst_token);
		token = node_token->content;
		if (token->type == DEFAULT)
			ft_lstadd_back(&ctrl->lst_args, node_token);
		else if (token->type == RDRT)
			ft_lstadd_back(&ctrl->lst_rdrt, ft_lstnew(parser_rdrt_new(
						node_token, ft_lstextract_front(lst_token))));
		else if (token->type == CTRL)
		{
			*condition = ctrl_value(token->value);
			ft_lstdelone(node_token, del_token);
			break ;
		}
		else if (token->type == SUBSH_BEGIN)
		{
			ctrl->ft_exe = exe_subsh;
			ctrl->exedel_ft = del_ctrl;
			ft_lstdelone(node_token, del_token);
			ft_lstadd_back(&ctrl->lst_args, ms_parser(lst_token));
		}
		else if (token->type == SUBSH_END)
		{
			*condition = NULL;
			ft_lstdelone(node_token, del_token);
			break ;
		}
	}
	return (ctrl);
}

t_list	*ms_parser(t_list **lst_token)
{
	t_list		*lst_ctrl;
	t_ftctrl	condition;

	lst_ctrl = NULL;
	condition = ctrl_continue;
	while (*lst_token != NULL && condition != NULL)
		ft_lstadd_back(&lst_ctrl, ft_lstnew(
				parser_ctrlnode(lst_token, &condition)));
	return (lst_ctrl);
}
