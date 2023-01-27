/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 12:18:39 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/01/27 12:35:14 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_routine_run(void)
{
	char	*input;
	char	**tokens_arr;
	t_node	*cmds;

	while (true)
	{
		input = readline("🐚 $ ");
		// if (!ft_strncmp(input, "exit", 4))
		// {
		// 	free(input);
		// 	input = NULL;
		// 	break ;
		// }
		if (input)
		{
			add_history(input);
			tokens_arr = ms_lexer(input);
			cmds = ms_parser(tokens_arr);
			ms_executor(cmds);
			free(input);
			input = NULL;
			
			//
			free(tokens_arr);
			ms_node_tree_free(cmds);
		}
	}
}
