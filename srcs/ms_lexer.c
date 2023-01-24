#include "minishell.h"

static char	*lexer_quote(char **ptr_src)
{
	char	quote;
	char	*end;
	char	*substr;

	quote = (*ptr_src)[0];
	if (!(quote == '\'' || quote == '\"'))
	{
		ft_dprintf(2, "Lexer_quote receiving non quote character: (%c) in (%s)\n",
			quote, (*ptr_src));
		return (NULL);
	}
	end = ft_strchr(&(*ptr_src)[1], quote);
	if (end == NULL)
	{
		ft_dprintf(2, "Missing closing quote (%c) in (%s)\n", quote, (*ptr_src));
		return (NULL);
	}
	substr = ft_substr((*ptr_src), 1, end - &(*ptr_src)[1]);
	(*ptr_src) = end;
	return (substr);
}

static char	*lexer_buffer(char **src)
{
	t_list	*buffer;
	char	*ptr;

	buffer = NULL;
	ptr = &(*src)[-1];
	while (*++ptr != '\0' && !ft_isspace(*ptr))
	{
		if (*ptr == '\\')
			shell_backslash(ptr);
		else if (*ptr == '\'' || *ptr == '\"')
		{
			ft_lstadd_back(&buffer, ft_lstnew(ft_substr(*src, 0, ptr - *src)));
			char	*parse = lexer_quote(&ptr);

			if (parse == NULL)
			{
				ft_lstclear(&buffer, free);
				return (NULL);
			}
			ft_lstadd_back(&buffer, ft_lstnew(parse));
			*src = ptr + 1;
		}
	}
	ft_lstadd_back(&buffer, ft_lstnew(ft_substr(*src, 0, ptr - *src)));
	*src = ptr;
	return (ft_lsttoa_clear(&buffer));
}

static char	**lexer_core(char *src)
{
	t_list	*lst;
	char	*arg;

	lst = NULL; 
	src--;
	while (*++src != '\0')
	{
		if (ft_isspace(*src))
			continue ;
		arg = lexer_buffer(&src);
		if (arg == NULL)
		{
			ft_lstclear(&lst, free);
			return (NULL);
		}
		ft_lstadd_back(&lst, ft_lstnew(arg));
		if (*src == '\0')
			break ;
	}
	// ft_lstiter(lst, lstiter_showstr);
	return (ft_lsttoaa_clear(&lst));
}

char	**ms_lexer(const char *src)
{
	char	*dup;
	char	**strlist;

	dup = ft_strdup(src);
	strlist = lexer_core(dup);
	free(dup);
	return (strlist);
}
