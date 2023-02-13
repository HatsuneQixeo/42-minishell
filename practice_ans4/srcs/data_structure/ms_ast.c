/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_ast.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:51:04 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/02/13 13:36:50 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_btree.h"
#include "ms_token.h"
#include "ms_double_linked_list.h"
#include "ms_debug.h"

char	**list_to_arr_str(t_double_list *literal_list)
{
	int		i;
	char	**arr;
	int		size_arr;

	i = -1;
	size_arr = double_lstsize(literal_list);
	arr = malloc(sizeof(char *) * (size_arr + 1));
	if (!arr)
		return (NULL);
	while (literal_list)
	{
		arr[++i] = ft_strdup(literal_list->content);
		literal_list = literal_list->next;
	}
	arr[size_arr] = NULL;
	return (arr);
}

void	literal_list_add_back(t_double_list **literal_list, char *token_value)
{
	char	*value;

	value = ft_strdup(token_value);
	double_lstadd_back(literal_list, double_lstnew(value));
}

void	ast_add_token_literal(t_node **root, t_double_list *literal_list)
{
	void	*arr_str;
	void	*ptr_token;

	if (!literal_list)
		return ;
	arr_str = list_to_arr_str(literal_list);
	ptr_token = (void *)ms_token_create(arr_str, TOKEN_LITERAL);
	btree_node_add(root, btree_node_init(ptr_token));
}

void	ast_add_token_operator(t_node **root, t_token *token)
{
	void	*arr_str;
	void	*ptr_token;	

	if (!token)
		return ;
	arr_str = ft_split(token->value, '\0');
	ptr_token = (void *)ms_token_create(arr_str, token->type);
	btree_node_add(root, btree_node_init(ptr_token));
}

void	ast_create(t_node **root, t_double_list *token_list)
{
	t_token			*token;
	t_double_list	*literal_list;

	literal_list = NULL;
	while (token_list)
	{
		token = token_list->content;
		if (ms_token_is_separator(token))
			break ;
		else if (ms_token_is_operator(token))
		{
			ast_add_token_literal(root, literal_list);
			double_lstclear(&literal_list, free);
			ast_add_token_operator(root, token);
		}
		else if (token->type != TOKEN_SPACE)
			literal_list_add_back(&literal_list, token->value);
		token_list = token_list->next;
	}
	ast_add_token_literal(root, literal_list);
	double_lstclear(&literal_list, free);
}

void	del_arr_str(void *arr_str)
{
	int		i;
	char	**arr;

	i = -1;
	arr = arr_str;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

void	ast_free(t_node **node)
{
	t_node	*n;
	t_token	*token;

	n = *node;
	if (!n)
		return ;
	token = n->content;
	ms_token_free2(token, del_arr_str);
	if (n->left)
		ast_free(&n->left);
	if (n->right)
		ast_free(&n->right);
	free(n);
	*node = NULL;
}