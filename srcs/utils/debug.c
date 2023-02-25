/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:21:07 by hqixeo            #+#    #+#             */
/*   Updated: 2023/02/25 18:26:23 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	lstshow_tmpname(t_list *lst, t_ftsetname ft_setname,
			const char *tmpname, t_ftlstiter ft_debug)
{
	const char	*name = ft_setname(NULL);

	ft_setname(tmpname);
	ft_lstiter(lst, ft_debug);
	ft_setname(name);
}
