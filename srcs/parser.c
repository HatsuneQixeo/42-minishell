/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 12:16:10 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/01/09 03:20:31 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_lstextract_front(t_list **lst)
{
	t_list	*node;

	if (*lst == NULL)
		return (NULL);
	node = *lst;
	(*lst) = (*lst)->next;
	node->next = NULL;
	return (node);
}

static t_ftexitstatus	ctrl_value(const t_token *token)
{
	if (!ft_strcmp(token->value, "&&"))
		return (ctrl_success);
	else if (!ft_strcmp(token->value, "||"))
		return (ctrl_failure);
	else if (!ft_strcmp(token->value, "|"))
		return (ctrl_any);
	else
		ft_dprintf(2, "ctrl_value does not recognize: %s\n", token->value);
	return (NULL);
}

void	del_ctrl(void *content)
{
	t_ctrl	*process;

	process = content;
	if (process->ft_exe == exe_argv)
		ft_lstclear(&process->lst_exe, del_token);
	else if (process->ft_exe == exe_subsh)
		ft_lstclear(&process->lst_exe, del_ctrl);
	else
		ft_dprintf(2, "del_ctrl does not recognize the ft_exe: %p\n", process->ft_exe);
	ft_lstclear(&process->lst_rdrt, del_token);
	free(process);
}

static t_ctrl	*ctrl_new(t_ftexitstatus condition, t_ftexe exe)
{
	t_ctrl	*ctrl;

	ctrl = malloc(sizeof(t_ctrl));
	if (ctrl == NULL)
		return (NULL);
	ctrl->condition = condition;
	ctrl->ft_exe = exe;
	ctrl->lst_exe = NULL;
	ctrl->lst_rdrt = NULL;
	return (ctrl);
}

static t_ctrl	*parser_recursive_node(t_list **lst_token, t_ftexitstatus *condition)
{
	t_ctrl	*ctrl;
	t_list	*node_token;
	t_token	*token;

	ctrl = ctrl_new(*condition, exe_argv);
	while (*lst_token != NULL)
	{
		node_token = ft_lstextract_front(lst_token);
		token = node_token->content;
		if (token->type == DEFAULT)
			ft_lstadd_back(&ctrl->lst_exe, node_token);
		else if (isoperator_ctrl(token->type))
		{
			*condition = ctrl_value(token);
			ft_lstdelone(node_token, del_token);
			break ;
		}
		else if (token->type == SUBSH_END)
		{
			*condition = NULL;
			ft_lstdelone(node_token, del_token);
			break ;
		}
		else if (isoperator_rdrt(token->type))
		{
			ft_lstadd_back(&ctrl->lst_rdrt, node_token);
			ft_lstadd_back(&ctrl->lst_rdrt, ft_lstextract_front(lst_token));
		}
		else if (token->type == SUBSH_BEGIN)
		{
			ctrl->ft_exe = exe_subsh;
			ft_lstdelone(node_token, del_token);
			ft_lstadd_back(&ctrl->lst_exe, parser_recursive(lst_token));
		}
	}
	return (ctrl);
}

t_list	*parser_recursive(t_list **lst_token)
{
	t_list			*lst_ctrl;
	t_ftexitstatus	condition;

	lst_ctrl = NULL;
	condition = ctrl_any;
	while (*lst_token != NULL && condition != NULL)
		ft_lstadd_back(&lst_ctrl, ft_lstnew(parser_recursive_node(lst_token, &condition)));
	return (lst_ctrl);
}

/**
 * @brief A successful prototype but is not qualified for norminette
 * Same as the one above currently during (20/1/2023 11.37pm)
 */

// t_list	*parser_recursive(t_list **lst_token);

// static t_ctrl	*parser_recursive_node(t_list **lst_token, t_ftexitstatus *condition)
// {
// 	t_ctrl	*ctrl;
// 	t_list	*node_token;
// 	t_token	*token;

// 	ctrl = ctrl_new(*condition, exe_argv);
// 	while (*lst_token != NULL)
// 	{
// 		node_token = ft_lstextract_front(lst_token);
// 		token = node_token->content;
// 		if (token->type == DEFAULT)
// 			ft_lstadd_back(&ctrl->lst_exe, node_token);
// 		else if (isoperator_ctrl(token->type))
// 		{
// 			*condition = ctrl_value(token);
// 			ft_lstdelone(node_token, del_token);
// 			break ;
// 		}
// 		else if (token->type == SUBSH_END)
// 		{
// 			ft_lstdelone(node_token, del_token);
// 			*condition = NULL;
// 			break ;
// 		}
// 		else if (isoperator_rdrt(token->type))
// 		{
// 			ft_lstadd_back(&ctrl->lst_rdrt, node_token);
// 			ft_lstadd_back(&ctrl->lst_rdrt, ft_lstextract_front(lst_token));
// 		}
// 		else if (token->type == SUBSH_BEGIN)
// 		{
// 			ctrl->ft_exe = exe_subsh;
// 			ft_lstdelone(node_token, del_token);
// 			ft_lstadd_back(&ctrl->lst_exe, parser_recursive(lst_token));
// 		}
// 	}
// 	return (ctrl);
// }

// t_list	*parser_recursive(t_list **lst_token)
// {
// 	t_list			*lst_ctrl;
// 	t_ftexitstatus	condition;

// 	lst_ctrl = NULL;
// 	condition = ctrl_any;
// 	while (*lst_token != NULL && condition != NULL)
// 		ft_lstadd_back(&lst_ctrl, ft_lstnew(parser_recursive_node(lst_token, &condition)));
// 	return (lst_ctrl);
// }
