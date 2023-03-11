/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 23:21:26 by hqixeo            #+#    #+#             */
/*   Updated: 2023/03/11 23:21:26 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_rdrt	*parse_rdrt_new(t_token *token_rdrt, t_token *token_arg)
{
	return (rdrt_new(rdrt_getft(token_rdrt->value), token_arg->value));
}

int	parse_rdrt(t_ctrl *ctrl, t_list **lst_token, t_ftctrl *condition)
{
	t_list	*node_rdrt;
	t_list	*node_arg;
	t_rdrt	*rdrt;

	node_rdrt = ft_lstextract_front(lst_token);
	node_arg = ft_lstextract_front(lst_token);
	rdrt = parse_rdrt_new(node_rdrt->content, node_arg->content);
	ft_lstadd_back(&ctrl->lst_rdrt, ft_lstnew(rdrt));
	ft_lstdelone(node_rdrt, del_token);
	ft_lstdelone(node_arg, free);
	return (0);
	(void)condition;
}

int	parse_ctrl(t_ctrl *ctrl, t_list **lst_token, t_ftctrl *condition)
{
	t_list	*node;
	t_token	*token;

	node = ft_lstextract_front(lst_token);
	token = node->content;
	*condition = ctrl_getft(token->value);
	ft_lstdelone(node, del_token);
	return (-1);
}

int	parse_subshbegin(t_ctrl *ctrl, t_list **lst_token, t_ftctrl *condition)
{
	ctrl->ft_exe = exe_subsh;
	ctrl->exedel_ft = del_ctrl;
	ft_lstdelone(ft_lstextract_front(lst_token), del_token);
	ft_lstadd_back(&ctrl->lst_args, ms_parser(lst_token));
	return (0);
	(void)condition;
}

int	parse_subshend(t_ctrl *ctrl, t_list **lst_token, t_ftctrl *condition)
{
	*condition = NULL;
	ft_lstdelone(ft_lstextract_front(lst_token), del_token);
	return (-1);
	(void)ctrl;
}
