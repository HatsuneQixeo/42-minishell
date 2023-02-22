/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 09:36:33 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/02/23 00:01:22 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_token_literal(t_token *token)
{
    char    *absolute_path;

    // absolute_path = absolute_path_find();
}

void	ms_executor(t_node *root)
{
	t_token_type	token_type;
	
	if (!root)
		return ;
    token_type = token_type_get(root->content);
	if (token_type == LITERAL)
		execute_token_literal(root->content);
		
}