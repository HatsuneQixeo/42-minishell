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

void	expd_expand(char **envp, t_list *lst_expdtoken)
{
	/* A little similar to heredoc_expand */
	t_token	*token;

	while (lst_expdtoken != NULL)
	{
		token = lst_expdtoken->content;
		if (token->type & EXPAND)
			token->value = ft_strmodify(strmod_replace, token->value,
					simpleexpand(envp, token->value));
		lst_expdtoken = lst_expdtoken->next;
	}
}
