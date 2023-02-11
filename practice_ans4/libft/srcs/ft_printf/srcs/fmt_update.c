/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmt_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 00:41:40 by ntan-wan          #+#    #+#             */
/*   Updated: 2022/07/24 17:11:36 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
   fmt_update : 
   Stores c/s/p/d/i/u/x/X/% format specifier.
*/
void	fmt_update(char c, t_fmt *fmt)
{
	if (c == 'c')
		fmt->c = 1;
	else if (c == 's')
		fmt->str = 1;
	else if (c == 'p')
		fmt->ptr = 1;
	else if (c == 'd')
		fmt->decimal = 1;
	else if (c == 'i')
		fmt->integer = 1;
	else if (c == 'u')
		fmt->unsi = 1;
	else if (c == 'x')
		fmt->hexa_lower = 1;
	else if (c == 'X')
		fmt->hexa_upper = 1;
	else if (c == '%')
		fmt->percent = 1;
}
