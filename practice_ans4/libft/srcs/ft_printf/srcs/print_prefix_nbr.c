/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_prefix_nbr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 01:09:35 by ntan-wan          #+#    #+#             */
/*   Updated: 2022/08/09 21:12:43 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include "../includes/libft.h"

/*
   This function is to print prefix and number character.
   This is used in print_decimal.c.
*/

void	print_prefix_nbr(t_fmt *fmt, int num, char *unsi_num_c)
{
	if (num < 0)
		ft_putchar_fd('-', 1);
	else if (fmt->space)
		ft_putchar_fd(' ', 1);
	else if (fmt->plus)
		ft_putchar_fd('+', 1);
	while (fmt->pad-- > 0)
		ft_putchar_fd('0', 1);
	ft_putstr_fd(unsi_num_c, 1);
}
