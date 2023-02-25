/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:21:06 by hqixeo            #+#    #+#             */
/*   Updated: 2023/02/25 18:26:23 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

int	ft_strprefix(const char *str, const char *prefix)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0' && prefix[i] != '\0')
	{
		if (str[i] != prefix[i])
			return (str[i] - prefix[i]);
		i++;
	}
	return (0);
}

static const t_token	*tokentype(const char *it)
{
	static const t_token	operators[] = {
	{CTRL, "&&"},
	{CTRL, "||"},
	{CTRL, "|"},
	{RDRT, "<<"},
	{RDRT, ">>"},
	{RDRT, "<"},
	{RDRT, ">"},
	{SUBSH_BEGIN, "("},
	{SUBSH_END, ")"},
	{DEFAULT, ""}
	};
	int						i;

	i = 0;
	while (ft_strprefix(it, operators[i].value))
		i++;
	return (&operators[i]);
}

static t_list	*lexer_lstnew_ifnempty(const char *src, const char *it)
{
	if (it == src)
		return (NULL);
	else
		return (ft_lstnew(token_new(ft_substr(src, 0, it - src), DEFAULT)));
}

t_list	*ms_lexer(const char *input_raw)
{
	t_list			*lst;
	const t_token	*token;
	const char		*it = input_raw - 1;

	lst = NULL;
	while (*++it != '\0')
	{
		if (ft_isquote(*it))
			it = ft_strchr(it + 1, *it);
		token = tokentype(it);
		if (!ft_isspace(*it) && token->type == DEFAULT)
			continue ;
		ft_lstadd_back(&lst, lexer_lstnew_ifnempty(input_raw, it));
		if (token->type != DEFAULT)
		{
			ft_lstadd_back(&lst, ft_lstnew(
					token_new(ft_strdup(token->value), token->type)));
			it += ft_strlen(token->value + 1);
		}
		input_raw = it + 1;
	}
	ft_lstadd_back(&lst, lexer_lstnew_ifnempty(input_raw, it));
	return (lst);
}
