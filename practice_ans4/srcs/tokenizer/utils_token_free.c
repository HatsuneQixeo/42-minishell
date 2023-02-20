/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 00:32:32 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/02/21 00:55:40 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_token.h"

void	token_free(void	*token)
{
	t_token	*t;

	t = token;
	free(t->value);
	free(t);
}

void	token_free_del(void *token, void (*del)(void *))
{
	t_token	*t;

	t = token;
	del(t->value);
	free(t);
}

void	token_list_free(t_double_list **token_list)
{
	double_lstclear(token_list, token_free);
}
