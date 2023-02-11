/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_c.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 12:28:02 by ntan-wan          #+#    #+#             */
/*   Updated: 2022/08/09 21:11:39 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include "../includes/libft.h"

/*
  Initialize print_len with 1 as a character guaranteed only 
  return 1 character.

  Only have to concerns with <width> and <negative> flags only.

  <no flag> = print a character only.

  <negative> only = runs the same as normal function,
  i.e, only print one character.

  <width> only = print 'spaces' first, then print 'character'.

  <negative> + <width> = print 'character' first, then print 'spaces'.
*/

int	print_c(t_fmt *fmt, int c)
{
	int	space_count;

	space_count = 0;
	fmt->print_len = 1;
	if (fmt->width)
	{
		space_count = fmt->width - 1;
		fmt->print_len = fmt->width;
		if (fmt->negative)
		{
			ft_putchar_fd(c, 1);
			while (space_count--)
				ft_putchar_fd(' ', 1);
		}
		else
		{
			while (space_count--)
				ft_putchar_fd(' ', 1);
			ft_putchar_fd(c, 1);
		}
	}
	else
		ft_putchar_fd(c, 1);
	return (fmt->print_len);
}
