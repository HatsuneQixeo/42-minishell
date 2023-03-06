#include "expander.h"

static t_list	*delimiter_split(const char *value)
{
	t_list		*lst_new;
	const char	*start = value;
	const char	*delimiter = ft_strchr_is(start, ft_isspace);

	lst_new = NULL;
	while (delimiter != NULL)
	{
		if (delimiter != start)
			ft_lstadd_back(&lst_new, ft_lstnew(token_new(
						ft_substr(start, 0, delimiter - start), PARSE)));
		start = ft_strskip_is(delimiter, ft_isspace);
		ft_lstadd_back(&lst_new, ft_lstnew(token_new(
					ft_substr(delimiter, 0, start - delimiter), SPACE)));
		delimiter = ft_strchr_is(start, ft_isspace);
	}
	if (start[0] != '\0')
		ft_lstadd_back(&lst_new, ft_lstnew(token_new(ft_strdup(start), PARSE)));
	return (lst_new);
}

void	expd_delimitertoken(t_list **lst)
{
	t_list	*lst_new;
	t_list	*node;
	t_token	*token;

	lst_new = NULL;
	while (*lst != NULL)
	{
		node = ft_lstextract_front(lst);
		token = node->content;
		if (~token->type & PARSE)
		{
			ft_lstadd_back(&lst_new, node);
			continue ;
		}
		ft_lstadd_back(&lst_new, delimiter_split(token->value));
		ft_lstdelone(node, del_token);
	}
	*lst = lst_new;
}
