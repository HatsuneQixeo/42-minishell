#include "expander.h"

static t_list	*wildcard_lexer(const char *str)
{
	const char	*wildcard = ft_strchr(str, '*');
	t_list		*lst_pattern;

	lst_pattern = NULL;
	while (wildcard != NULL)
	{
		ft_lstadd_back(&lst_pattern, ft_lstnew(ft_substr(str, 0, wildcard - str)));
		str = ft_strskip_chr(wildcard, '*');
		wildcard = ft_strchr(str, '*');
	}
	ft_lstadd_back(&lst_pattern, ft_lstnew(ft_strdup(str)));
	return (lst_pattern);
}

static t_list	*wildcard_joinbuffer(const char *value, char **p_buffer)
{
	t_list	*lst_wildcard;

	lst_wildcard = wildcard_lexer(value);
	lst_wildcard->content = ft_strcombine(*p_buffer, lst_wildcard->content);
	*p_buffer = NULL;
	return (lst_wildcard);
}

t_list	*wildcard_lstpattern(t_list *lst_token)
{
	t_list	*lst_pattern;
	char	*buffer;
	t_token	*token;

	lst_pattern = NULL;
	buffer = NULL;
	while (lst_token != NULL)
	{
		token = lst_token->content;
		if (token->type & PARSE && ft_strchr(token->value, '*'))
			ft_lstadd_back(&lst_pattern, wildcard_joinbuffer(token->value, &buffer));
		else
			buffer = ft_strmodify(ft_strjoin, buffer, token->value);
		lst_token = lst_token->next;
	}
	if (lst_pattern == NULL)
		free(buffer);
	else if (buffer != NULL)
		// ft_lstadd_back(&lst_pattern, ft_lstnew(buffer));
	{
		t_list	*last = ft_lstlast(lst_pattern);

		last->content = ft_strcombine(last->content, buffer);
	}
	return (lst_pattern);
}
