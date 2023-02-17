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

typedef struct s_control
{
	t_ftexitstatus	condition;
	/**
	 * @brief Question:
	 * What should this ptr point to
	 * ex: Like a lst of arguments, like cmdchunk
	 * ex: or a subshell, how should I act is this is subsh
	 * What if this is a function take takes in a linked list?
	 * That solves it?
	 */
	t_ftexe			ft_exe;
	t_list			*cmdchunk;
	/* (cat) < infile? This count as a cmd block no? */
	t_list			*rdrt_token;
}			t_ctrl;

void	lstiter_showctrl(int i, void *content)
{
	t_ctrl		*process;
	const char	*name_condition;

	process = content;
	if (process->condition == ctrl_any)
		name_condition = "ctrl_any";
	else if (process->condition == ctrl_success)
		name_condition = "ctrl_success";
	else if (process->condition == ctrl_failure)
		name_condition = "ctrl_failure";
	else
		name_condition = "undefined function";
	ft_printf("process{%d}: %s\n", i, name_condition);
	// if (process->ft_exe == exe_argc)
	ft_lstiter(process->cmdchunk, lstiter_showtoken);
	ft_printf("\n");
}

void	del_ctrl(void *content)
{
	t_ctrl	*process;

	process = content;
	if (process->ft_exe == exe_argv)
		ft_lstclear(&process->cmdchunk, del_token);
	else if (process->ft_exe == exe_subsh)
		ft_lstclear(&process->cmdchunk, del_ctrl);
	else
		ft_dprintf(2, "del_ctrl does not recognize the ft_exe: %p\n", process->ft_exe);
	free(process);
}

t_token	*lst_gettoken(t_list *node)
{
	if (node == NULL)
		return (NULL);
	else
		return (node->content);
}

t_list	*ft_lstextract_front(t_list **lst)
{
	t_list	*node;

	node = *lst;
	(*lst) = (*lst)->next;
	node->next = NULL;
	return (node);
}

t_ftexe	ctrl_nesting(t_list **start, t_list *end, t_list **lst_main, t_list **lst_rdrt)
{
	t_list	*tmp;
	t_ftexe	exeft;

	/* Maybe, I can check the syntax in this loop */
	/* if token->type == SUBSH_OPEN; ft_exe = */
	exeft = exe_argv;
	while ((*start)->next != end)
	{
		t_list	*node = ft_lstextract_front(start);
		{
			t_token	*token = node->content;

			if (token->type == SUBSH_BEGIN)
			{
				exeft = exe_subsh;
				/* Recursive call */
			}
			else if (token->type == DEFAULT)
				ft_lstadd_back(lst_main, node);
			else if (isoperator_rdrt(token->type))
			{
				ft_lstadd_back(lst_rdrt, node);
				ft_lstadd_back(lst_rdrt, ft_lstextract_front(start));
				if (!ft_strcmp(token->value, "<<"))
				{
					/* get heredoc */
				}
			}
			else if (token->type == SUBSH_END)
			{
				return (exeft);
			}
		}
	}
	/* Need to deal with this somehow , maybe move this down before tmp */
	if (end != NULL)
	{
		tmp = (*start)->next->next;
		(*start)->next = NULL;
		*start = tmp;
	}
	return (exeft);
}

t_ctrl	*ctrl_cmdchunk(t_list **start, t_list *end, t_ftexitstatus condition)
{
	t_ctrl	*ctrl;

	if (*start == end)
		return (NULL);
	ctrl = malloc(sizeof(t_ctrl));
	if (ctrl == NULL)
		return (NULL);
	ctrl->condition = condition;
	ctrl->cmdchunk = NULL;
	ctrl->rdrt_token = NULL;
	ctrl->ft_exe = ctrl_nesting(start, end, &ctrl->cmdchunk, &ctrl->rdrt_token);
	return (ctrl);
}

/**
 * @brief Parser
 * -> syntax check (might wanna heredoc here too?)
 * -> redirect
 * -> ctrl
 * -> cmdchunk
 * 
 * @param lst_token 
 * @return t_list* 
 */

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
	t_list			*node;
	t_token			*token;

	lst_ctrl = NULL;
	it = *lst_token;
	condition = ctrl_any;
	while (it != NULL)
	{
		token = it->content;
		if (token->type == SUBSH_END)
			break ;
		node = it;
		it = it->next;
		if (!isoperator_ctrl(token->type))
			continue ;
		ft_lstadd_back(&lst_ctrl, ft_lstnew(
				ctrl_cmdchunk(lst_token, node, condition)));
		if (!ft_strcmp(token->value, "&&"))
			condition = ctrl_success;
		else if (!ft_strcmp(token->value, "||"))
			condition = ctrl_failure;
		else if (!ft_strcmp(token->value, "|"))
			condition = ctrl_any;
		else
			ft_dprintf(2, "Unknown token in parser_ctrl pass isoperator_ctrl: %s\n", token->value);
		ft_lstdelone(node, del_token);
	}
	ft_lstadd_back(&lst_ctrl, ft_lstnew(
			ctrl_cmdchunk(lst_token, it, condition)));
	*lst_token = NULL;
	ft_lstiter(lst_ctrl, lstiter_showctrl);
	ft_lstclear(&lst_ctrl, del_ctrl);
	return (lst_ctrl);
}

const char	*ctrl_name(t_ftexitstatus condition)
{
	if (condition == ctrl_any)
		return ("ctrl_any");
	else if (condition == ctrl_success)
		return ("ctrl_success");
	else if (condition == ctrl_failure)
		return ("ctrl_failure");
	else
		return ("undefined function");
}

void	show_ctrl_core(t_list *lst_ctrl, int padding)
{
	int	i;

	i = 0;
	while (lst_ctrl != NULL)
	{
		t_ctrl	*node = lst_ctrl->content;

		lst_ctrl = lst_ctrl->next;
		ft_printf("ctrl[%d]: %s\n", i, ctrl_name(node->condition));
		if (node->ft_exe == exe_argv)
		{
			ft_printf("padding: %d\n", padding);
			ft_lstiter(node->cmdchunk, lstiter_showtoken);
		}
		else if (node->ft_exe == exe_subsh)
			show_ctrl_core(node->cmdchunk, (padding + 4));
		else
			ft_printf("Show_ctrl: Unknown ft in ft_exe: %p\n", node->ft_exe);
		i++;
	}
}

void	show_ctrl(t_list *lst_ctrl)
{
	show_ctrl_core(lst_ctrl, 0);
}

