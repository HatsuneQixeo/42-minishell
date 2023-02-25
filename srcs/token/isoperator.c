/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isoperator.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:21:07 by hqixeo            #+#    #+#             */
/*   Updated: 2023/02/25 10:21:07 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

int	isoperator_ctrl(enum e_tokentype type)
{
	return (type == CTRL);
}

int	isoperator_rdrt(enum e_tokentype type)
{
	return (type == RDRT);
}

int	isoperator_subsh(enum e_tokentype type)
{
	return (type == SUBSH_BEGIN || type == SUBSH_END);
}
