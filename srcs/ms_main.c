/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 12:10:40 by ntan-wan          #+#    #+#             */
/*   Updated: 2022/12/20 12:29:01 by ntan-wan         ###   ########.fr       */
/*                                                                           */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_env	*env;

	env = ms_env_init(envp);
	util_clear_screen();
	ms_signals_handler();
	ms_routine_run();
	return (EXIT_SUCCESS);
}
