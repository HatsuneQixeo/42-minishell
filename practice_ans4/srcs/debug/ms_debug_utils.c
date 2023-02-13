/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_debug_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:01:23 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/02/13 10:10:02 by ntan-wan         ###   ########.fr       */
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

void	debug_ast_content_print(t_node *root, int depth)
{
	int		i;
	t_token	*token;
	char	**token_value;

	if (!root)
		return ;
	i = -1;
	token = root->content;
	token_value = token->value;
	while (++i < depth)
		printf(" ");
	i = -1;
	while (token_value[++i])
		printf("%s ", token_value[i]);
	printf("\n");
	debug_ast_content_print(root->left, depth + 2);
	debug_ast_content_print(root->right, depth + 2);
}