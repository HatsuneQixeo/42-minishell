#include "expander.h"

static void	*map_token_getstr(void *content)
{
	const t_token	*token = content;

	return (token->value);
}

static char	*ft_lsttoken_tostr(t_list *lst_token)
{
	t_list	*lst_str;
	char	*str;

	lst_str = ft_lstmap(lst_token, map_token_getstr, free);
	str = ft_lsttostr(lst_str);
	ft_lstclear(&lst_str, NULL);
	return (str);
}

t_list	*wildcard_parsing(t_list *lst_token)
{
	t_list	*lst_pattern;
	char	**matched_filenames;

	lst_pattern = wildcard_lstpattern(lst_token);
	if (lst_pattern == NULL)
		return (ft_lstnew(ft_lsttoken_tostr(lst_token)));
	matched_filenames = wildcard_expand(lst_pattern);
	ft_lstclear(&lst_pattern, free);
	if (matched_filenames[0] == NULL)
	{
		free(matched_filenames);
		return (ft_lstnew(ft_lsttoken_tostr(lst_token)));
	}
	return (ft_aatolst_clear((void **)matched_filenames));
}
