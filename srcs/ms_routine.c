/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 12:18:39 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/01/09 03:13:28 by ntan-wan         ###   ########.fr       */
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
		if (input)
		{
			add_history(input);
			tokens_arr = ms_lexer(input);
			cmds = ms_parser(tokens_arr);
			ms_executor(cmds);
		}
		free(input);
	}
}
