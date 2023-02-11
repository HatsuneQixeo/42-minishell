/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmt_update_flags.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 13:58:38 by ntan-wan          #+#    #+#             */
/*   Updated: 2022/08/09 21:10:59 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include "../includes/libft.h"

/*
   This function stores info about flags.

   If the character is a digit, we convert it into a number using the formula
   below.

   We classify the number as percision if the number is after a "dot" or "zero".

   Next, we have to differentiate character '0' between <flag> and <width>.
   We classify '0' as flag if it appears before any number, i.e, before width.
   if fmt->width is not "true", meaning no number appeared in the string, '0'
   is a flag indeed then.
*/

void	fmt_update_flags(char c, t_fmt *fmt)
{
	if (ft_isdigit(c))
	{
		if (fmt->dot)
			fmt->percision = (fmt->percision * 10) + (c - '0');
		else
		{
			if (c == '0' && !fmt->width && !fmt->negative)
				fmt->zero = 1;
			else
				fmt->width = (fmt->width * 10) + (c - '0');
		}
	}
	else if (c == '-')
		fmt->negative = 1;
	else if (c == '.')
		fmt->dot = 1;
	else if (c == '#')
		fmt->hash = 1;
	else if (c == ' ')
		fmt->space = 1;
	else if (c == '+')
		fmt->plus = 1;
}
