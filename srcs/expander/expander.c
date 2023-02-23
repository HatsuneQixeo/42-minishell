#include "expander.h"

/* This function returns a new token with given value (shallow copy) */
static void	*lstmap_str_to_def_token(void *value)
{
	return (token_new(value, DEFAULT));
}

/* The default prototype, return a list of default tokens */
t_list	*expand_lst_argv(char **envp, t_token *token)
{
	t_list	*lst_expanded_args;
	t_list	*lst_mapped_token;

	lst_expanded_args = expand_arg(envp, token->value);
	lst_mapped_token = ft_lstmap(lst_expanded_args,
			lstmap_str_to_def_token, del_token);
	ft_lstclear(&lst_expanded_args, NULL);
	return (lst_mapped_token);
}

/* The experimental, Assuming the given list only contain default tokens */
// t_list	*expand_lst_argv(char **envp, t_token *token)
// {
// 	return (expand_arg(envp, token->value));
// }

t_list	*expand_lst_rdrt(char **envp, t_token *token)
{
	static int	isheredoc;

	if (isheredoc)
	{
		isheredoc = 0;
		return (ft_lstnew(token_new(ft_strdup(token->value), DEFAULT)));
	}
	else if (!ft_strcmp(token->value, "<<"))
		isheredoc = 1;
	if (isoperator_rdrt(token->type))
		return (ft_lstnew(token_new(ft_strdup(token->value), RDRT)));
	else if (token->type == DEFAULT)
		return (expand_lst_argv(envp, token));
	/*
		Oh no, where should the ambiguous original token be?
		I need a tmp for that
		I dunno, just make a data structure for it?
	*/
	ft_dprintf(2, "Unknown type of token in lst_rdrt: ");
	lstiter_showtoken(-831, token);
	return (NULL);
}

t_list	*ms_expander(char **envp, t_list *lst, t_ftexpand ft_expand)
{
	t_list	*lst_new;

	lst_new = NULL;
	while (lst != NULL)
	{
		ft_lstadd_back(&lst_new, ft_expand(envp, lst->content));
		lst = lst->next;
	}
	return (lst_new);
}
