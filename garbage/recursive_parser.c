/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:20:58 by hqixeo            #+#    #+#             */
/*   Updated: 2023/02/25 10:20:58 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief This is an incomplete prototype
 * 
 * @param start 
 * @param end 
 * @param condition 
 * @return t_ctrl* 
 */

t_ctrl	*ctrl_nesting(t_list **start, t_list *end, t_ftexitstatus condition)
{
	t_ctrl	*node_ctrl;

	node_ctrl = ctrl_new(condition, exe_argv);
	if (node_ctrl == NULL)
		return (NULL);
	while ((*start)->next != end)
	{
		t_list	*node = ft_lstextract_front(start);
		{
			t_token	*token = node->content;

			if (token->type == SUBSH_BEGIN)
			{
				node_ctrl->ft_exe = exe_subsh;
				/* Deleting subsh_begin */
				ft_lstdelone(ft_lstextract_front(start), del_token);
				ft_lstadd_back(&node_ctrl->lst_exe, parser_ctrl(start));
				/* Deleting subsh_end */
				ft_lstdelone(ft_lstextract_front(start), del_token);
				/* Recursive call */
			}
			else if (token->type == DEFAULT)
				ft_lstadd_back(node_ctrl->lst_exe, node);
			else if (isoperator_rdrt(token->type))
			{
				ft_lstadd_back(node_ctrl->rdrt_token, node);
				ft_lstadd_back(node_ctrl->rdrt_token, ft_lstextract_front(start));
				if (!ft_strcmp(token->value, "<<"))
				{
					/* get heredoc */
				}
			}
			else if (token->type == SUBSH_END)
			{
				return (node_ctrl);
			}
		}
	}
	if (end != NULL)
	{
		t_list	*tmp;

		tmp = (*start)->next->next;
		(*start)->next = NULL;
		*start = tmp;
	}
	else
		*start = NULL;
	return (node_ctrl);
}

/**
 * @brief 
 * 
 * @param lst_token 
 * @return t_list* A list of t_ctrl, which contains
 */
t_list	*parser_ctrl(t_list **lst_token)
{
	t_list			*lst_ctrl;
	t_list			*it;
	t_ftexitstatus	condition;

	lst_ctrl = NULL;
	it = *lst_token;
	condition = ctrl_continue;
	while (it != NULL)
	{
		t_token	*token = it->content;
		t_list	*node = it;

		if (token->type == SUBSH_END)
			break ;
		it = it->next;
		if (!isoperator_ctrl(token->type))
			continue ;
		ft_lstadd_back(&lst_ctrl, ft_lstnew(
				ctrl_nesting(lst_token, node, condition)));
		condition = ctrl_value(token);
		/* safety trigger */
		if (condition == NULL)
			exit(1);
		ft_lstdelone(node, del_token);
	}
	ft_lstadd_back(&lst_ctrl, ft_lstnew(
			ctrl_nesting(lst_token, it, condition)));
	show_ctrl(lst_ctrl);
	return (lst_ctrl);
}

/**
 * @brief Another failed prototype due to immature sectioning (t_list *end)
 * 
 * @param lst_token 
 * @return t_list* 
 */
t_list	*parser_ctrl(t_list **lst_token);

static t_ctrl	*ctrl_frame(t_list **start, t_list *end, t_ftexitstatus condition)
{
	t_ctrl	*content_ctrl;

	content_ctrl = ctrl_new(condition, exe_argv);
	if (content_ctrl == NULL)
		return (NULL);
	while (*start != NULL && (*start) != end)
	{
		t_list	*node = ft_lstextract_front(start);
		t_token	*token = node->content;

		if (token->type == SUBSH_BEGIN)
		{
			content_ctrl->ft_exe = exe_subsh;
			ft_lstdelone(node, del_token);
			ft_lstadd_back(&content_ctrl->lst_exe, parser_ctrl(start));
			/* Deleting the subsh_end token */
			if (*start != NULL)
			{
				const char	*original = lstname_token(NULL);
				lstname_token("ctrl_frame");
					lstshow_token(-1, (*start)->content);
				lstname_token(original);
			ft_lstdelone(ft_lstextract_front(start), del_token);
			}
		}
		else if (isoperator_rdrt(token->type))
		{
			ft_lstadd_back(&content_ctrl->rdrt_token, node);
			ft_lstadd_back(&content_ctrl->rdrt_token, ft_lstextract_front(start));
		}
		else
			ft_lstadd_back(&content_ctrl->lst_exe, node);
	}
	ft_lstdelone(ft_lstextract_front(start), del_token);
	return (content_ctrl);
}

/**
 * @brief 
 * 
 * @param lst_token 
 * @return t_list* A list of t_ctrl, which contains
 */
t_list	*parser_ctrl(t_list **lst_token)
{
	t_list			*lst_ctrl;
	t_list			*it;
	t_ftexitstatus	condition;

	lst_ctrl = NULL;
	it = *lst_token;
	condition = ctrl_continue;
	ft_printf("parser_ctrl receiving: \n");
	ft_lstiter(*lst_token, lstshow_token);
	ft_printf("\n");
	while (it != NULL)
	{
		t_list	*node = it;
		t_token	*token = node->content;

		if (token->type == SUBSH_END)
		{
			ft_printf("breaking parser_ctrl: \n");
			ft_lstiter(it, lstshow_token);
			ft_printf("\n");
			break ;
		}
		it = it->next;
		if (!isoperator_ctrl(token->type))
			continue ;
		ft_lstadd_back(&lst_ctrl, ft_lstnew(ctrl_frame(lst_token, node, condition)));
		condition = ctrl_value(token);
		/* safety trigger */
		if (condition == NULL)
			exit(2);
	}
	ft_lstadd_back(&lst_ctrl, ft_lstnew(ctrl_frame(lst_token, it, condition)));
	return (lst_ctrl);
}
