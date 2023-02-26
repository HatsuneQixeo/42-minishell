/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_operator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:21:06 by hqixeo            #+#    #+#             */
/*   Updated: 2023/02/25 18:26:22 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_common.h"

// int	ctrl_any(void)
// {
// 	return (1);
// }

int	ctrl_continue(void)
{
	return (1);
}

int	ctrl_success(void)
{
	return (g_lastexit == 0);
}

int	ctrl_failure(void)
{
	return (g_lastexit != 0);
}
