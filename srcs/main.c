/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 12:10:40 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/11 23:21:26 by hqixeo           ###   ########.fr       */
/*                                                                           */
/* ************************************************************************** */

#include "minishell.h"
#include "ms_common.h"

// ft_printf("\e[1;1H\e[2J");
int	main(int argc, char **argv, char **envp)
{
	minishell(envp);
	leakcheck("Program end");
	(void)argc;
	(void)argv;
}
