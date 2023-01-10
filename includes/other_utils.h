/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 00:52:27 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/01/09 03:27:24 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OTHER_UTILS_H
# define OTHER_UTILS_H

# include <unistd.h>
# include <stdlib.h>

# include "libft.h"

void	util_clear_screen(void);
int		util_str_arr_len(char **arr);
char	**util_str_arr_dup(char **arr);
void	*util_realloc(void *ptr, size_t old_size, size_t new_size);
void	util_str_arr_free(char ***array);
#endif