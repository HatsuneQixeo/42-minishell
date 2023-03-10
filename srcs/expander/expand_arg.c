/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expd_parse_expand.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:22:16 by hqixeo            #+#    #+#             */
/*   Updated: 2023/03/07 15:22:16 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static void	expd_expand(char **envp, t_list *lst_expdtoken)
{
	t_token	*token;
	/* A little similar to heredoc_expand */

	while (lst_expdtoken != NULL)
	{
		token = lst_expdtoken->content;
		if (token->type & EXPAND)
			token->value = ft_strmodify(strmod_replace, token->value,
					simpleexpand(envp, token->value));
		lst_expdtoken = lst_expdtoken->next;
	}
}

static void	bash_shenanigan(char *str)
{
	while (*str != '\0')
	{
		if (*str == '$' && ft_isquote(*(str + 1)))
			ft_memmove(str, str + 1, ft_strlen(str + 1) + 1);
		if (ft_isquote(*str))
			str = ft_strchr(str + 1, *str);
		str++;
	}
}

t_list	*expand_arg(char **envp, char *value)
{
	t_list	*lst_test;

	bash_shenanigan(value);
	lst_test = expd_tokenizer(value);
	expd_expand(envp, lst_test);
	expd_delimitertoken(&lst_test);
	lst_test = expd_parse(&lst_test);
	return (lst_test);
}
