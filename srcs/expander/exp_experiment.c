#include "expander.h"

void	expd_expand(char **envp, t_list *lst_expdtoken)
{
	/* A little similar to heredoc_expand */
	t_token	*token;

	while (lst_expdtoken != NULL)
	{
		token = lst_expdtoken->content;
		if (token->type & EXPAND)
			token->value = ft_strmodify(strmod_replace, token->value,
					simpleexpand(envp, token->value));
		lst_expdtoken = lst_expdtoken->next;
	}
}

/*
	The purpose of this function is to finalize the tokens
	Joining every token, treating space token as delimiter

	Evaluating wildcard character in parse token and find the matching file,
	and join every file as their individual argument
*/
t_list	*expd_parse(t_list **lst)
{
	t_list	*lst_parsed;
	t_list	*lst_buffer;
	t_list	*node;
	t_token	*token;

	lst_parsed = NULL;
	lst_buffer = NULL;
	while (*lst != NULL)
	{
		node = ft_lstextract_front(lst);
		token = node->content;
		if (token->type & SPACE)
		{
			ft_lstadd_back(&lst_parsed, wildcard_parsing(lst_buffer));
			ft_lstclear(&lst_buffer, del_token);
			ft_lstdelone(node, del_token);
		}
		else
			ft_lstadd_back(&lst_buffer, node);
	}
	ft_lstadd_back(&lst_parsed, wildcard_parsing(lst_buffer));
	ft_lstclear(&lst_buffer, del_token);
	return (lst_parsed);
}
