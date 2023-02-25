/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer_argv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:20:58 by hqixeo            #+#    #+#             */
/*   Updated: 2023/02/25 10:20:58 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*lexer_parse_quote(char **src)
{
	const char	quote = (*src)[0];
	const char	*end = ft_strchr(&(*src)[1], quote);
	char		*substr;

	if (!ft_isquote(quote))
		ft_dprintf(2, "lexer_parse_quote receiving non quote character:"
			"(%c) in (%s)\n",
			quote, (*src));
	else if (end == NULL)
		ft_dprintf(2, "Missing closing quote (%c) in (%s)\n", quote, (*src));
	else
	{
		substr = ft_substr((*src), 1, end - &(*src)[1]);
		(*src) = (char *)end;
		return (substr);
	}
	return (NULL);
}

char	*lexer_parse_arg(char **src)
{
	t_list	*buffer;
	char	*ptr;
	char	*parse_quote;

	buffer = NULL;
	ptr = &(*src)[-1];
	while (*++ptr != '\0' && !ft_isspace(*ptr))
	{
		if (!ft_isquote(*ptr))
			continue ;
		ft_lstadd_back(&buffer, ft_lstnew(ft_substr((*src), 0, ptr - (*src))));
		parse_quote = lexer_parse_quote(&ptr);
		if (parse_quote == NULL)
		{
			ft_lstclear(&buffer, free);
			return (NULL);
		}
		ft_lstadd_back(&buffer, ft_lstnew(parse_quote));
		(*src) = ptr + 1;
	}
	ft_lstadd_back(&buffer, ft_lstnew(ft_substr((*src), 0, ptr - (*src))));
	(*src) = ptr;
	return (ft_lsttostr_clear(&buffer));
}

char	**ms_lexer(const char *src)
{
	t_list	*lst;
	char	*arg;
	char	*it;

	lst = NULL; 
	it = (char *)src;
	while (*it != '\0')
	{
		if (ft_isspace(*it))
		{
			it++;
			continue ;
		}
		arg = lexer_parse_arg(&it);
		if (arg == NULL)
		{
			ft_lstclear(&lst, free);
			return (NULL);
		}
		ft_lstadd_back(&lst, ft_lstnew(arg));
	}
	return ((char **)ft_lsttoaa_clear(&lst));
}
