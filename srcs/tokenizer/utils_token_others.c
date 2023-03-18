/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token_others.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 09:10:56 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/18 07:32:48 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rm_token_value(t_token *token)
{
	if (!token)
		return ;
	if (token->value)
	{
		ft_bzero(token->value, ft_strlen(token->value));
		token->type = LITERAL;
	}
}

t_token	*concat_2_tokens(t_token *token1, t_token *token2, t_token_type type)
{
	char	*value;

	value = ft_strjoin(token1->value, token2->value);
	return (token_create(value, type));
}

/* 
	@brief Set the token type of the following list as set_type.
	@param set_type set the token type.
 */
void	list_token_type_set(t_double_list *list, t_token_type set_type)
{
	t_token_type	init_type;
	t_token_type	type;

	if (!list)
		return ;
	init_type = token_type_get(list->content);
	while (list)
	{
		type = token_type_get(list->content);
		if (type != init_type)
			break ;
		token_type_set(list->content, set_type);
		list = list->next;
	}
}

t_token	*token_dup(t_token *token)
{
	t_token	*new_token;

	if (!token)
		return (NULL);
	new_token = ft_calloc(1, sizeof(t_token));
	new_token->value = ft_strdup(token->value);
	new_token->type = token->type;
	return (new_token);
}
