/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 14:54:25 by ntan-wan          #+#    #+#             */
/*   Updated: 2022/08/09 21:13:55 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include "../includes/libft.h"

/*
	This function is used in print_percent and print_ptr to
	print spaces.
*/

void	print_space(t_fmt *fmt, int space_count)
{
	char	space;

	space = ' ';
	if (fmt->zero && !fmt->ptr)
		space = '0';
	while (space_count-- > 0)
		ft_putchar_fd(space, 1);
}
