#include "expander.h"

void	exp_expander(char **envp, t_list *lst_exptoken)
{
	/* A little similar to heredoc_expand */
	t_token	*token;

	while (lst_exptoken != NULL)
	{
		token = lst_exptoken->content;
		if (token->type & EXPAND)
			token->value = ft_strmodify(strmod_replace, token->value,
					simpleexpand(envp, token->value));
		lst_exptoken = lst_exptoken->next;
	}
}

t_list	*delimiter_split(const char *value)
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

t_list	*exp_delimiter(t_list **lst)
{
	t_list	*lst_new;
	t_list	*node;
	t_token	*token;

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
	return (lst_new);
}

/*
	The purpose of this function is to finalize the tokens
	Joining every token, treating space token as delimiter

	Evaluating wildcard character in parse token and find the matching file,
	and join every file as their individual argument
*/
t_list	*exp_parse(t_list **lst)
{
	t_list	*lst_parsed;
	t_list	*lst_buffer;

	lst_parsed = NULL;
	lst_buffer = NULL;
	lstname_token("before parse");
	ft_lstiter(*lst, lstshow_expandtoken);
	lstname_token("token");
	ft_lstclear(lst, del_token);
	while (*lst != NULL)
	{
		t_list	*node = ft_lstextract_front(lst);
		t_token	*token = node->content;

		if (token->type & SPACE)
		{
			if (lst_buffer != NULL)
				ft_lstadd_back(&lst_parsed, ft_lstnew(
						ft_lsttostr_clear(&lst_buffer)));
			continue ;
		}
		if (~token->type & PARSE)
		{
			ft_lstadd_back(&lst_buffer, node);
			continue ;
		}
		/* Evaluate parse argument */
	}
	return (lst_parsed);
}
