/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_other_utils.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 21:40:13 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/02/15 11:06:13 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_OTHER_UTILS_H
# define MS_OTHER_UTILS_H

# include <stdlib.h>

# include "libft.h"
# include "ms_double_linked_list.h"

void	util_clear_screen(void);
void	util_del_arr_str(void *arr_str);
char	**util_list_to_arr_str(t_double_list *literal_list);
#endif