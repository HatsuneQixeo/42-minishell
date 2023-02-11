/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_debug.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:04:10 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/02/11 14:34:07 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_DEBUG_H
# define MS_DEBUG_H

# include <stdio.h>

# include "ms_token.h"

void    debug_token_content_print(void *content);
void	debug_token_list_content_print(t_double_list *list);
#endif