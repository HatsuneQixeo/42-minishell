/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 12:10:40 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/16 02:21:41 by hqixeo           ###   ########.fr       */
/*                                                                           */
/* ************************************************************************** */
#include "minishell.h"

// ft_printf("\e[1;1H\e[2J");
int	main(int argc, char **argv, char **envp)
{
	minishell(envp);
	(void)argc;
	(void)argv;
}
