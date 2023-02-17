#include "minishell.h"

static char	*lexer_doublequote(char **src)
{
	char	*ptr_src;
	t_list	*lst;

	lst = NULL;
	ptr_src = (*src)++;
	while (*++ptr_src != '\0' && *ptr_src != '\"')
	{
		if (*ptr_src == '\\')
			shell_backslash(ptr_src);
		else if (*ptr_src == '$')
		{
			ft_lstadd_back(&lst, ft_lstnew(ft_substr(*src, 0, ptr_src - *src)));
			ft_lstadd_back(&lst, ft_lstnew(expander_node(&ptr_src)));
			*src = ptr_src + 1;
		}
	}
	ft_lstadd_back(&lst, ft_lstnew(ft_substr(*src, 0, ptr_src - *src)));
	if (*ptr_src == '\"')
	{
		*src = ptr_src;
		return (ft_lsttostr_clear(&lst));
	}
	ft_dprintf(2, "Missing closing quote (%c) in (%s)\n", '\"', (*src)[-1]);
	ft_lstclear(&lst, free);
	return (NULL);
}

static char	*lexer_singlequote(char **src)
{
	char	*end;
	char	*substr;

	end = ft_strchr(&(*src)[1], '\'');
	if (end == NULL)
	{
		ft_dprintf(2, "Missing closing quote (%c) in (%s)\n", '\'', *src);
		return (NULL);
	}
	substr = ft_substr((*src), 1, end - (*src) - 1);
	*src = end;
	return (substr);
}

char	*lexer_quote(char **src)
{
	char	quote;

	quote = **src;
	// ft_printf("Lexer_quote is receiving: %s\n", *src);
	if (quote == '\'')
		return (lexer_singlequote(src));
	else if (quote == '\"')
		return (lexer_doublequote(src));
	ft_dprintf(2, "ft_parsequote"
		" receiving non quote character: (%c) in (%s)\n", quote, *src);
	return (NULL);
}
