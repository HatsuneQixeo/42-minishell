/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_ast.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:51:04 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/02/11 11:31:13 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_btree.h"
#include "ms_token.h"

// void    ast_create(t_node **parent, t_list **token_list)
// {
// 	t_list	*list;
// 	t_token *token;

// 	if (!parent || !token_list || !*token_list)
// 		return ;
// 	list = *token_list;
// 	while (list)
// 	{
// 		token = list->content;
// 		if (ms_token_is_separator(token))
// 			break ;
// 		else if (ms_token_is_operator(token))
// 		{
				
// 		}
// 		list = list->next;
// 	}
// }
