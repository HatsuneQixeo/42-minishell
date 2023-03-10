/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_scanner2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 11:30:39 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/10 11:31:08 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	s_free(t_scanner **scanner)
{
	if (!*scanner)
		return ;
	token_list_free(&(*scanner)->token_list);
	free(*scanner);
	*scanner = NULL;
}
