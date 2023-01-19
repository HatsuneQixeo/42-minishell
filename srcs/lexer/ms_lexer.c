#include "minishell.h"

char	*lexer_quote(char **src);

static char	*lexer_buffer(char **src)
{
	t_list	*buffer;
	char	*ptr;

	buffer = NULL;
	ptr = *src - 1;
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
		else if (*ptr == '$')
		{
			ft_lstadd_back(&buffer, ft_lstnew(ft_substr(*src, 0, ptr - *src)));
			ft_lstadd_back(&buffer, ft_lstnew(expander_node(&ptr)));
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
	ft_lstiter(lst, lstiter_showstr);
	// ft_strrelease_fd(ft_strmodify(ft_lsttoa(lst), "Lst: ", ft_strrjoin), 1);
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
