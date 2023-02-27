/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 12:10:40 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/02/27 16:12:49 by hqixeo           ###   ########.fr       */
/*                                                                           */
/* ************************************************************************** */

#include "minishell.h"
#include "ms_common.h"

int	main(int argc, char **argv, char **envp)
{
	ft_printf("\e[1;1H\e[2J");
	minishell(envp);
	leakcheck("mainend");
	(void)argc;
	(void)argv;
}
