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

static t_ftexitstatus	ctrl_value(const t_token *token)
{
	if (!ft_strcmp(token->value, "&&"))
		return (ctrl_success);
	else if (!ft_strcmp(token->value, "||"))
		return (ctrl_failure);
	else if (!ft_strcmp(token->value, "|"))
		return (ctrl_continue);
	else
		ft_dprintf(2, "ctrl_value does not recognize: %s\n", token->value);
	return (NULL);
}

static t_ctrl	*parser_ctrlnode(char **envp, t_list **lst_token, t_ftexitstatus *condition)
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
			t_list	*rdrt_arg = ft_lstextract_front(lst_token);

			if (!ft_strcmp(token->value, "<<"))
			{
				t_token	*rdrt_arg_token = rdrt_arg->content;
				rdrt_arg_token->value = parser_heredoc(envp, rdrt_arg_token->value);
			}
			ft_lstadd_back(&ctrl->lst_rdrt, rdrt_arg);
		}
		else if (token->type == SUBSH_BEGIN)
		{
			ctrl->ft_exe = exe_subsh;
			ft_lstdelone(node_token, del_token);
			ft_lstadd_back(&ctrl->lst_exe, ms_parser(envp, lst_token));
		}
	}
	return (ctrl);
}

t_list	*ms_parser(char **envp, t_list **lst_token)
{
	t_list			*lst_ctrl;
	t_ftexitstatus	condition;

	lst_ctrl = NULL;
	condition = ctrl_continue;
	while (*lst_token != NULL && condition != NULL)
		ft_lstadd_back(&lst_ctrl, ft_lstnew(
			parser_ctrlnode(envp, lst_token, &condition)));
	return (lst_ctrl);
}
