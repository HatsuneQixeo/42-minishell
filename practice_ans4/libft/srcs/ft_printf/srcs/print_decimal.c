/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_decimal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 17:08:06 by ntan-wan          #+#    #+#             */
/*   Updated: 2022/08/09 21:11:54 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include "../includes/libft.h"

/*
	calc_num_len :
	Count total characters, including '-' character, of the number.

	unsi_num_c_alloc :
	Allocate appropriate memory.
	
	(listed in absolute.c)
	absolute :
	Convert number to positive number.

	(listed in print_unsi.c)
	ft_uitoa :
	Convert unsigned int to character.
	
	flags_int :
	1. percision > number characters excluding '+' or '-' :
	   Padding required.
	2. width > pad + characters including '+' or '-' :
	   offset required.
	3. <space> or <plus> flags raised, number is positive, and 
	   there is offset :
	   Minus 1 offset value to make space for '+' or ' '.
	4. <zero> flag raised and <dot> flag is not raised :
	   Transfer offset value to pad so that '0' will print in
	   between 'sign' character and number characters.

	print_order :
	Decides how the output will look like.
	1. <negative> flag is raised :
	   Offset is printed after the number characters.
	2. <negative> flag is not raised :
	   Offset is printed before number characters.

	(listed in print_prefix_nbr.c)
	print_prefix_nbr :
	Print prefix first, number characters later.
	
	print_decimal :
	The core function.
	1. " if (num != 0 || !fmt->dot || fmt->percision) " :
	   Prevent memory from being allocated when num is zero, 
	   dot flag is raised and no percision value.
	   e.g : ("%.d", 0) -> (nothing should print out, thus no
	   memory should be allocated).
*/

int	calc_num_len(int num, int base)
{
	int	count;

	count = 0;
	if (num <= 0)
		++count;
	while (num && ++count)
		num /= base;
	return (count);
}

char	*unsi_num_c_alloc(int num)
{
	char	*rtn;
	int		unsi_num;

	unsi_num = absolute(num);
	rtn = ft_uitoa(unsi_num);
	return (rtn);
}

void	flags_int(t_fmt *fmt, int num, int num_len, int unsi_num_c_len)
{
	if (fmt->percision > unsi_num_c_len)
		fmt->pad = fmt->percision - unsi_num_c_len;
	if (fmt->width > fmt->pad + num_len)
		fmt->offset = fmt->width - fmt->pad - num_len;
	if (fmt->space || fmt->plus)
	{
		if (num >= 0 && ++fmt->print_len && fmt->offset)
			--fmt->offset;
	}
	fmt->print_len += fmt->offset + fmt->pad + num_len;
	if (fmt->zero && !fmt->dot)
	{
		fmt->pad = fmt->offset;
		fmt->offset = 0;
	}
}

void	print_order_int(t_fmt *fmt, int num, char *unsi_num_c)
{
	if (fmt->negative)
	{
		print_prefix_nbr(fmt, num, unsi_num_c);
		while (fmt->offset--)
			ft_putchar_fd(' ', 1);
	}
	else
	{
		while (fmt->offset--)
			ft_putchar_fd(' ', 1);
		print_prefix_nbr(fmt, num, unsi_num_c);
	}
}

int	print_decimal(t_fmt *fmt, int num)
{
	int		num_len;
	char	*unsi_num_c;
	int		unsi_num_c_len;

	num_len = 0;
	unsi_num_c = "";
	if (num != 0 || !fmt->dot || fmt->percision)
	{
		num_len = calc_num_len(num, 10);
		unsi_num_c = unsi_num_c_alloc(num);
	}
	unsi_num_c_len = (int)ft_strlen(unsi_num_c);
	flags_int(fmt, num, num_len, unsi_num_c_len);
	print_order_int(fmt, num, unsi_num_c);
	if (num != 0 || !fmt->dot || fmt->percision)
		free(unsi_num_c);
	return (fmt->print_len);
}
