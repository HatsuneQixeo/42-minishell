/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_lexer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:22:16 by hqixeo            #+#    #+#             */
/*   Updated: 2023/03/07 15:22:16 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static t_list	*wildcard_lexer(const char *str)
{
	const char	*wildcard = ft_strchr(str, '*');
	t_list		*lst_pattern;

	lst_pattern = NULL;
	ft_dprintf(2, "lexer lexing: [%s]\n", str);
	while (wildcard != NULL)
	{
		ft_lstadd_back(&lst_pattern, ft_lstnew(
				ft_substr(str, 0, wildcard - str)));
		str = ft_strskip_chr(wildcard, '*');
		wildcard = ft_strchr(str, '*');
	}
	ft_lstadd_back(&lst_pattern, ft_lstnew(ft_strdup(str)));
	lstshow_name("lst_pattern");
	ft_lstiter(lst_pattern, lstshow_str);
	lstshow_name(LSTNAME_DEFAULT);
	return (lst_pattern);
}

static void	wildcard_joinbuffer(t_list **lst_pattern,
			const char *value, char **p_buffer)
{
	t_list	*lst_wildcard;
	t_list	*lst_last;

	lst_wildcard = wildcard_lexer(value);
	lst_wildcard->content = ft_strcombine(*p_buffer, lst_wildcard->content);
	*p_buffer = NULL;
	lst_last = ft_lstlast(*lst_pattern);
	if (lst_last != NULL)
	{
		lst_last->content = ft_strmodify(ft_strjoin,
				lst_last->content, lst_wildcard->content);
		ft_lstdelone(ft_lstextract_front(&lst_wildcard), NULL);
	}
	ft_lstadd_back(lst_pattern, lst_wildcard);
}

static t_list	*ft_normslave(t_list *lst_pattern, char *buffer)
{
	t_list	*last;

	if (lst_pattern == NULL)
		free(buffer);
	else if (buffer != NULL)
	{
		last = ft_lstlast(lst_pattern);
		last->content = ft_strcombine(last->content, buffer);
	}
	return (lst_pattern);
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
			wildcard_joinbuffer(&lst_pattern, token->value, &buffer);
		else
			buffer = ft_strmodify(ft_strjoin, buffer, token->value);
		lst_token = lst_token->next;
	}
	return (ft_normslave(lst_pattern, buffer));
}
