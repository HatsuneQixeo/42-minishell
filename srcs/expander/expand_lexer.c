#include "expander.h"

void	lstshow_expandtoken(void *content)
{
	const t_token	*token = content;
	char			str_type[39];

	str_type[0] = '\0';
	if (token->type & EXPAND)
		ft_strlcat(str_type, CYAN"Expand", sizeof(str_type));
	if (token->type & PARSE)
		ft_strlcat(str_type, YELLOW"Parse", sizeof(str_type));
	if (token->type & SPACE)
		ft_strlcat(str_type, MAGENTA"Space", sizeof(str_type));
	if (token->type == LITERAL)
		ft_strlcat(str_type, GREY"Literal", sizeof(str_type));
	if (str_type[0] == '\0')
		ft_strlcat(str_type, RED"Unknown", sizeof(str_type));
	ft_dprintf(2, "%s: %-8s: [%b]\n"DEF,
		lstname_token(NULL), str_type, token->value);
}

static t_token	*expand_quotetoken(const char **it)
{
	const char	quote = **it;
	const char	*start = &(*it)[1];
	const char	*it_end = ft_strchr(start, quote);

	*it = it_end;
	if (quote == '\'')
		return (token_new(ft_substr(start, 0, it_end - start), LITERAL));
	else if (quote == '\"')
		return (token_new(ft_substr(start, 0, it_end - start), EXPAND));
	ft_dprintf(2, "expand_quotetoken receiving non quote pointer: %s\n", *it);
	*it = start - 1;
	return (NULL);
}

t_list	*expand_lexer(const char *arg)
{
	t_list		*lst_extoken;
	const char	*it = arg - 1;

	lst_extoken = NULL;
	while (*++it != '\0')
	{
		/*
			What about space?

			No, any given space not inside quote should already been excluded,
			and space in quote should be preserved, no problem here

			The space only come from unquoted expand variable,
			which is marked together with * by PARSE
		*/
		if (!ft_isquote(*it))
			continue ;
		if (it != arg)
			ft_lstadd_back(&lst_extoken, ft_lstnew(token_new(
						ft_substr(arg, 0, it - arg), EXPAND + PARSE)));
		ft_lstadd_back(&lst_extoken, ft_lstnew(expand_quotetoken(&it)));
		arg = it + 1;
	}
	if (it != arg)
		ft_lstadd_back(&lst_extoken, ft_lstnew(token_new(
					ft_substr(arg, 0, it - arg), EXPAND + PARSE)));
	return (lst_extoken);
}
