/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expd_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:22:16 by hqixeo            #+#    #+#             */
/*   Updated: 2023/03/16 02:21:41 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static t_list	*wildcard(t_list *lst_token)
{
	t_list	*lst_pattern;
	char	**matched_filenames;

	lst_pattern = wc_lexer(lst_token);
	if (lst_pattern == NULL)
		return (ft_lstnew(ft_lsttoken_tostr(lst_token)));
	matched_filenames = wc_expand(lst_pattern);
	ft_lstclear(&lst_pattern, free);
	if (matched_filenames[0] == NULL)
	{
		free(matched_filenames);
		return (ft_lstnew(ft_lsttoken_tostr(lst_token)));
	}
	return (ft_aatolst_clear((void **)matched_filenames));
}

void	expd_parse(t_list **lst)
{
	t_list	*lst_parsed;
	t_list	*lst_buffer;
	t_list	*node;
	t_token	*token;

	lst_parsed = NULL;
	lst_buffer = NULL;
	while (*lst != NULL)
	{
		node = ft_lstextract_front(lst);
		token = node->content;
		if (token->type & DELIMITER)
		{
			ft_lstadd_back(&lst_parsed, wildcard(lst_buffer));
			ft_lstclear(&lst_buffer, del_token);
			ft_lstdelone(node, del_token);
		}
		else
			ft_lstadd_back(&lst_buffer, node);
	}
	ft_lstadd_back(&lst_parsed, wildcard(lst_buffer));
	ft_lstclear(&lst_buffer, del_token);
	*lst = lst_parsed;
}
