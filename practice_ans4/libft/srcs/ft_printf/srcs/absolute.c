/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   absolute.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 17:53:23 by ntan-wan          #+#    #+#             */
/*   Updated: 2022/08/09 21:10:01 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include "../includes/libft.h"

unsigned int	absolute(int num)
{
	unsigned int	unsi_num;

	unsi_num = num;
	if (num < 0)
	{
		unsi_num = -unsi_num;
		return (unsi_num);
	}
	else
		return (unsi_num);
}
