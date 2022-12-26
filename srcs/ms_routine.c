/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 12:18:39 by ntan-wan          #+#    #+#             */
/*   Updated: 2022/12/26 17:08:22 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ms_routine_run(void)
{
	char	*input;

	while (true)
	{
		input = readline("🐚 $ ");
		if (input)
		{
			add_history(input);
			ms_tokenize(input);
		}
		free(input);
	}
}
