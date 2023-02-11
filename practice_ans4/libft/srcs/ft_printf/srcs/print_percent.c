/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_percent.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 18:26:10 by ntan-wan          #+#    #+#             */
/*   Updated: 2022/08/09 21:12:25 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include "../includes/libft.h"

/*
   Same implementation as print_c. The only differnce is that we have to 
   concern with <zero> flag as well.

   If there is <zero>, we change 'spaces' to 'zero' instead. This is
   handled in print_space funtion.

   print_space :
   Print spaces accordingly. 
*/

int	print_percent(t_fmt *fmt)
{
	int		space_count;

	space_count = 0;
	fmt->print_len = 1;
	if (fmt->width)
	{
		space_count = fmt->width - 1;
		fmt->print_len = fmt->width;
		if (fmt->negative)
		{
			ft_putchar_fd('%', 1);
			print_space(fmt, space_count);
		}
		else
		{
			print_space(fmt, space_count);
			ft_putchar_fd('%', 1);
		}
	}
	else
		ft_putchar_fd('%', 1);
	return (fmt->print_len);
}
