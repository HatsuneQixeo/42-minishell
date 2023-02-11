/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_s.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 14:52:29 by ntan-wan          #+#    #+#             */
/*   Updated: 2022/08/09 21:13:36 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include "../includes/libft.h"

/*
   " if (!fmt->dot || fmt->percision > fmt->print_len) " :
   1. If percision value is more than string length, percision value
      is equal to string length.
*/

int	print_s(t_fmt *fmt, char *str)
{
	if (!str)
		str = "(null)";
	fmt->print_len = (int)ft_strlen(str);
	if (!fmt->dot || fmt->percision > fmt->print_len)
		fmt->percision = fmt->print_len;
	if (fmt->width > fmt->percision)
		fmt->offset = fmt->width - fmt->percision;
	fmt->print_len = fmt->offset + fmt->percision;
	if (fmt->negative)
	{
		write(1, str, fmt->percision);
		while (fmt->offset--)
			ft_putchar_fd(' ', 1);
	}
	else
	{
		while (fmt->offset--)
			ft_putchar_fd(' ', 1);
		write(1, str, fmt->percision);
	}
	return (fmt->print_len);
}
