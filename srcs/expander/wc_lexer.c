/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:22:16 by hqixeo            #+#    #+#             */
/*   Updated: 2023/03/16 02:21:41 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "expander.h"

static t_list	*wc_parsetoken(const char *str)
{
	const char	*wildcard = ft_strchr(str, '*');
	t_list		*lst_pattern;

	lst_pattern = NULL;
	while (wildcard != NULL)
	{
		ft_lstadd_back(&lst_pattern, ft_lstnew(
				ft_substr(str, 0, wildcard - str)));
		str = ft_strskip_chr(wildcard, '*');
		wildcard = ft_strchr(str, '*');
	}
	ft_lstadd_back(&lst_pattern, ft_lstnew(ft_strdup(str)));
	return (lst_pattern);
}

void	lststr_joinlast(t_list *lst_str, const char *str)
{
	t_list	*last;

	if (lst_str == NULL)
		return ;
	last = ft_lstlast(lst_str);
	last->content = ft_strmodify(ft_strjoin, last->content, str);
}

static void	wc_parse_addback(t_list **lst_pattern,
			const char *value, char **p_buffer)
{
	t_list	*lst_wildcard;

	lst_wildcard = wc_parsetoken(value);
	lst_wildcard->content = ft_strcombine(*p_buffer, lst_wildcard->content);
	*p_buffer = NULL;
	if (*lst_pattern != NULL)
	{
		lststr_joinlast(*lst_pattern, lst_wildcard->content);
		ft_lstdelone(ft_lstextract_front(&lst_wildcard), free);
	}
	ft_lstadd_back(lst_pattern, lst_wildcard);
}

t_list	*wc_lexer(t_list *lst_token)
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
			wc_parse_addback(&lst_pattern, token->value, &buffer);
		else
			buffer = ft_strmodify(ft_strjoin, buffer, token->value);
		lst_token = lst_token->next;
	}
	if (lst_pattern != NULL && buffer != NULL)
		lststr_joinlast(lst_pattern, buffer);
	free(buffer);
	return (lst_pattern);
}
