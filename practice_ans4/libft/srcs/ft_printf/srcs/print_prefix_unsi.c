/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_prefix_unsi.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 21:37:30 by ntan-wan          #+#    #+#             */
/*   Updated: 2022/08/09 21:12:59 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include "../includes/libft.h"

void	print_prefix_unsi(t_fmt *fmt, char *unsi_num_c)
{
	if (fmt->space)
		ft_putchar_fd(' ', 1);
	else if (fmt->plus)
		ft_putchar_fd('+', 1);
	while (fmt->pad-- > 0)
		ft_putchar_fd('0', 1);
	ft_putstr_fd(unsi_num_c, 1);
}
