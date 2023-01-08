/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 12:16:10 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/01/09 03:03:19 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* 
	@brief	Store tokens in Abstract Syntax Tree.
	@retval	parent nodes.
 */
t_node	*ms_parser(char **tokens_arr)
{
	int		i;
	t_node	*cmd;
	t_node	*word;

	if (!tokens_arr)
		return (NULL);
	i = -1;
	cmd = ms_node_init(NODE_COMMAND);
	while (tokens_arr[++i])
	{
		word = ms_node_init(NODE_VAR);
		ms_set_node_val_str(word, tokens_arr[i]);
		ms_node_child_add(cmd, word);
	}
	return (cmd);
}