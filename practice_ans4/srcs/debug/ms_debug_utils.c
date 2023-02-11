/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_debug_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:01:23 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/02/11 14:33:51 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_debug.h"

void    debug_token_content_print(void *content)
{
	t_token	*t;	

	t = content;
	printf("value -> %s\n", (char *)t->value);
	printf("type -> %d\n", t->type);
}

void	debug_token_list_content_print(t_double_list *list)
{
	double_lstiter(list, debug_token_content_print);
}