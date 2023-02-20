#include "minishell.h"

/**
 * @brief Abandoned due to making access to resource too complicated to access that it should
 * 
 * @param lst_ctrl 
 * @return t_list* 
 */

t_list	*parser_getsubsh(t_list **lst_ctrl)
{
	t_list	*lst_subsh;
	t_list	*node_ctrl = ft_lstextract_front(lst_ctrl);
	t_ctrl	*ctrl = node_ctrl->content;

	ctrl->ft_exe = exe_subsh;
	/* Deleting the subsh_begin token */
	lst_subsh = NULL;
	while (ctrl->lst_exe != NULL)
	{
		/* Extract the first node in lst_exe */
		t_list	*node = ft_lstextract_front(&ctrl->lst_exe);
		/* Extract the token */
		t_token	*token = node->content;

		if (token->type == SUBSH_END)
			return (lst_subsh);
		else if (token->type == SUBSH_BEGIN)
		{
			ft_lstdelone(node, del_token);
			ft_lstadd_back(&lst_subsh, parser_getsubsh(lst_ctrl));
		}
	}
	
	return (NULL);
}

t_list	*parser_partition(t_list **lst_ctrl)
{
	t_list	*node_ctrl = (*lst_ctrl);
	t_ctrl	*ctrl_content = node_ctrl->content;
	t_token	*first_token = ctrl_content->lst_exe->content;

	if (first_token->type == SUBSH_BEGIN)
		return (parser_getsubsh(lst_ctrl));
	else
		return (node_ctrl);
}

t_list	*parser_subshell(t_list **lst_ctrl)
{
	t_list	*lst_partitioned;

	lst_partitioned = NULL;
	/* Nuh uh, not yet */
	return (NULL);
	while (*lst_ctrl != NULL)
		ft_lstadd_back(&lst_partitioned, parser_partition(lst_ctrl));
	return (lst_partitioned);
}


// t_list	*parser_partition(t_list **lst_ctrl_resources)
// {
// 	t_list	*res_node = ft_lstextract_front(lst_ctrl_resources);
// 	t_ctrl	*res_content = res_node->content;
// 	t_list	*ret_node = res_node;
// 	t_ctrl	*ret_content;

// 	res_content->ft_exe = exe_argv;
// 	while (res_content->lst_exe != NULL)
// 	{
// 		t_token	*token = res_content->lst_exe->content;

// 		if (token->type == SUBSH_BEGIN)
// 		{
// 			res_content->ft_exe = exe_subsh;
// 			ft_lstdelone(ft_lstextract_front(&res_content->lst_exe), del_token);
// 			ft_lstadd_back(&ret_node, parser_partition(&res_content->lst_exe));
// 		}
// 		else if (token->type == SUBSH_END)
// 		{
// 			ft_lstdelone(ft_lstextract_front(&res_content->lst_exe), del_token);

// 			t_ctrl	*partition_ctrl = ret_node->content;
// 			ft_printf("I should be argv too in a subsh?(depends on nesting): %s\n",
// 					ctrl_name(partition_ctrl->condition));

// 			return (ret_node);
// 		}
// 		else if (token->type == RDRT)
// 		{
// 			ft_lstadd_back(&res_content->rdrt_token, ft_lstextract_front(res_content->lst_exe));
// 			ft_lstadd_back(&res_content->rdrt_token, ft_lstextract_front(res_content->lst_exe));
// 		}
// 		else
// 			ft_lstadd_back(&res_content->lst_exe, ft_lstextract_front(ptt_content->lst_exe));
// 	}
// 	(*lst_ctrl_resources) = (*lst_ctrl_resources)->next;

// 	t_ctrl	*partition_ctrl = ret_node->content;
// 	ft_printf("I think I'm argv?: %s\n", ctrl_name(partition_ctrl->condition));

// 	return (ret_node);



// 	return (NULL);
// }
