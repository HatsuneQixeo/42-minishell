#include "expander.h"
#include "rdrt.h"

/* The experimental, Assuming the returned list only contain default tokens */
t_list	*expand_lst_argv(char **envp, void *ptr_token)
{
	const t_token	*token = ptr_token;

	return (expand_arg(envp, token->value));
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
