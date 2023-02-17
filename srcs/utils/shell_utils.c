/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_other_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 12:05:17 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/01/09 03:29:34 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isquote(int c)
{
	return (c == '\'' || c == '\"');
}

int	ft_isnameletter(int c)
{
	return (ft_isalnum(c) || c == '_');
}

void	ft_cleanterminal(void)
{
	ft_printf("\e[1;1H\e[2J");
}

void	ms_perror(const char *name)
{
	ft_dprintf(2, MINISHELL": ");
	perror(name);
}
