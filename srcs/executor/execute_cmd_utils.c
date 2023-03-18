/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 10:38:57 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/18 13:25:49 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_argc_get(t_ast *cmd_node)
{
	int	count;

	count = 0;
	while (cmd_node)
	{
		count++;
		cmd_node = cmd_node->right;
	}
	return (count);
}

char	**cmd_argv_init(t_ast *cmd_node)
{
	int		i;
	int		argc;
	char	**argv;

	i = -1;
	argv = NULL;
	argc = cmd_argc_get(cmd_node);
	while (cmd_node && cmd_node->data)
	{
		if (!argv)
		{
			argv = ft_calloc(argc + 1, sizeof(char *));
			argv[argc] = NULL;
		}
		argv[++i] = ft_strdup(cmd_node->data);
		cmd_node = cmd_node->right;
	}
	return (argv);
}
