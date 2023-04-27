/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expd_tokenizer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:22:16 by hqixeo            #+#    #+#             */
/*   Updated: 2023/03/16 02:21:41 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "expander.h"

void	lstshow_expandtoken(void *content)
{
	const t_token	*token = content;
	char			str_type[831];

	str_type[0] = '\0';
	if (token->type & EXPAND)
		ft_strlcat(str_type, ANSI_CYAN"Expand", sizeof(str_type));
	if (token->type & PARSE)
		ft_strlcat(str_type, ANSI_YELLOW"Parse", sizeof(str_type));
	if (token->type & DELIMITER)
		ft_strlcat(str_type, ANSI_MAGENTA"Delimiter", sizeof(str_type));
	if (token->type == LITERAL)
		ft_strlcat(str_type, ANSI_GREY"Literal", sizeof(str_type));
	if (str_type[0] == '\0')
		ft_strlcat(str_type, ANSI_RED"Unknown", sizeof(str_type));
	ft_dprintf(2, "%s: %-8s: [%b]\n"ANSI_RESET,
		lstname_token(NULL), str_type, token->value);
}

static t_token	*expd_tokenquote(const char **it)
{
	const char	quote = **it;
	const char	*start = &(*it)[1];
	const char	*it_end = ft_strchr(start, quote);

	*it = it_end;
	if (quote == '\'')
		return (token_new(ft_substr(start, 0, it_end - start), LITERAL));
	else if (quote == '\"')
		return (token_new(ft_substr(start, 0, it_end - start), EXPAND));
	ft_dprintf(2, "expd_tokenquote receiving non quote pointer: %s\n", *it);
	*it = start - 1;
	return (NULL);
}

t_list	*expd_tokenizer(const char *arg)
{
	t_list		*lst_extoken;
	const char	*it = arg - 1;

	lst_extoken = NULL;
	while (*++it != '\0')
	{
		if (!ft_isquote(*it))
			continue ;
		if (it != arg)
			ft_lstadd_back(&lst_extoken, ft_lstnew(token_new(
						ft_substr(arg, 0, it - arg), EXPAND + PARSE)));
		ft_lstadd_back(&lst_extoken, ft_lstnew(expd_tokenquote(&it)));
		arg = it + 1;
	}
	if (it != arg)
		ft_lstadd_back(&lst_extoken, ft_lstnew(token_new(
					ft_substr(arg, 0, it - arg), EXPAND + PARSE)));
	return (lst_extoken);
}
