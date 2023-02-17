#include "minishell.h"

int	ctrl_next(t_list **lst, t_list *it)
{
	t_token	*node;
	t_token	*next;

	node = it->content;
	if (!isoperator_ctrl(node->type))
	{
		ft_dprintf(2, "ctrl_next receiving not ctrl token: %s\n", node->value);
		return (-1);
	}
	if (it->next == NULL)
	{
		syntax_error(NULL);
		return (-1);
	}
	next = it->next->content;
	if (isoperator_ctrl(next->type)
		|| next->type == CTRL_PIPE || next->type == SUBSH_END)
	{
		syntax_error(next);
		return (-1);
	}
	free(node->value);
	node->value = next->value;
	/* Delete the node */
	ft_lstremove(lst, it->next, free);
	return (0);
}

int	subsh_begin_next(t_list **lst, t_list *it)
{
	t_token	*node;
	t_token	*next;

	node = it->content;
	if (node->type != SUBSH_BEGIN)
	{
		ft_dprintf(2, "subsh_begin_next receiving not subsh_begin token: %s\n", node->value);
		return (-1);
	}
	if (it->next == NULL)
	{
		syntax_error(NULL);
		return (-1);
	}
	next = it->next->content;
	if (next->type == CTRL_PIPE || isoperator_ctrl(next->type))
	{
		syntax_error(next);
		return (-1);
	}
	free(node->value);
	node->value = next->value;
	/* delete the node */
	ft_lstremove(lst, it->next, free);
	return (0);
}

int	subsh_end_next(t_list **lst, t_list *it)
{
	t_token	*node;
	t_token	*next;

	node = it->content;
	if (node->type != SUBSH_END)
	{
		ft_dprintf(2, "subsh_end_next receiving not subsh_end token: %s\n", node->value);
		return (-1);
	}
	if (it->next == NULL)
	{
		syntax_error(NULL);
		return (-1);
	}
	next = it->next->content;
	if (next->type == DEFAULT || next->type == SUBSH_BEGIN)
	{
		syntax_error(next);
		return (-1);
	}
	free(node->value);
	node->value = next->value;
	/* delete the node */
	ft_lstremove(lst, it->next, free);
	return (0);
}

int	rdrt_next(t_list **lst, t_list *it)
{
	t_token	*node;
	t_token	*next;

	node = it->content;
	if (!isoperator_rdrt(node->type))
	{
		ft_dprintf(2, "rdrt_next receiving not rdrt token: %s\n", node->value);
		return (-1);
	}
	if (it->next == NULL)
	{
		syntax_error(NULL);
		return (-1);
	}
	next = it->next->content;
	if (next->type != DEFAULT)
	{
		syntax_error(next);
		return (-1);
	}
	free(node->value);
	node->value = next->value;
	/* delete the node */
	ft_lstremove(lst, it->next, free);
	return (0);
}
