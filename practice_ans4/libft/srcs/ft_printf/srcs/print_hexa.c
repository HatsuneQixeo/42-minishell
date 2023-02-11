/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 18:02:24 by ntan-wan          #+#    #+#             */
/*   Updated: 2022/08/09 21:12:09 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include "../includes/libft.h"

/*
   convert_hexa :
   Convert unsigned int to hexadecimal. 
   First, determine which base you want to use. Next, allocate approriate memory 
   with the help of hexa_len. After that, place the character obtained into the
   'array' starting from the back. For example :
   1234 -> 4D2
        -> | | |2|
	-> | |D|2|
	-> |4|D|2|
   
   print_prefix_hexa :
   Print prefix for hexadecimal.
   1. " if (fmt->hash && hexa_c[0] != '0') ":
      Print  prefix "0x" or "0X" only if <hash> flag is raised and the number
      is not 0.

   flags_hexa :
   1. If <hash> flag is raised and there is width value:
      Subtract 2 from width value because the width value here control
      offset value too. Print 2 less offset as two 'slots' are reserved
      for "0x" or "0X".
   2. If percision value > hexa characters' length:
      pad value is equal to percision value - hexa characters' length.

   print_order_hexa :
   Decides how the output looks like.

   print_hexa :
   The core function.
   1. " if (unsi_num != 0 || !fmt->dot || fmt->percision) ":
      Prevent memory from being allocated when these conditons are 
      satisfied : num is 0, <dot> flag is raised and there is no
      percision value.
      e.g : ("%.x", 0) -> (nothing should print out, thus no
      memory should be allocated).
*/

char	*convert_hexa(t_fmt *fmt, unsigned int unsi_num)
{
	int		hexa_len;
	char	*hexa_c;
	char	*base;

	base = "0123456789abcdef";
	if (fmt->hexa_upper)
		base = "0123456789ABCDEF";
	hexa_len = calc_unsi_num_len(unsi_num, 16);
	hexa_c = (char *)malloc(sizeof(char) * (hexa_len + 1));
	if (!hexa_c)
		return (0);
	if (unsi_num == 0)
		hexa_c[0] = '0';
	hexa_c[hexa_len] = '\0';
	while (unsi_num != 0)
	{
		hexa_c[hexa_len - 1] = base[unsi_num % 16];
		unsi_num /= 16;
		hexa_len--;
	}
	return (hexa_c);
}

void	print_prefix_hexa(t_fmt *fmt, char *hexa_c)
{
	if (fmt->hash && hexa_c[0] != '0')
	{
		if (fmt->hexa_lower)
			fmt->print_len += write(1, "0x", 2);
		else if (fmt->hexa_upper)
			fmt->print_len += write(1, "0X", 2);
	}
	while (fmt->pad-- > 0)
		ft_putchar_fd('0', 1);
	ft_putstr_fd(hexa_c, 1);
}

void	flags_hexa(t_fmt *fmt, int hexa_len, int hexa_c_len)
{
	if (fmt->hash && fmt->width)
		fmt->width -= 2;
	if (fmt->percision > hexa_c_len)
		fmt->pad = fmt->percision - hexa_c_len;
	if (fmt->width > fmt->pad + hexa_len)
		fmt->offset = fmt->width - fmt->pad - hexa_len;
	fmt->print_len += fmt->offset + fmt->pad + hexa_len;
	if (fmt->zero && !fmt->dot)
	{
		fmt->pad = fmt->offset;
		fmt->offset = 0;
	}
}

void	print_order_hexa(t_fmt *fmt, char *hexa_c)
{
	if (fmt->negative)
	{
		print_prefix_hexa(fmt, hexa_c);
		while (fmt->offset--)
			ft_putchar_fd(' ', 1);
	}
	else
	{
		while (fmt->offset--)
			ft_putchar_fd(' ', 1);
		print_prefix_hexa(fmt, hexa_c);
	}
}

int	print_hexa(t_fmt *fmt, unsigned int unsi_num)
{
	char	*hexa_c;
	int		hexa_c_len;
	int		hexa_len;

	hexa_c = "";
	hexa_len = 0;
	if (unsi_num != 0 || !fmt->dot || fmt->percision)
	{
		hexa_c = convert_hexa(fmt, unsi_num);
		hexa_len = calc_unsi_num_len(unsi_num, 16);
	}
	hexa_c_len = (int)ft_strlen(hexa_c);
	flags_hexa(fmt, hexa_len, hexa_c_len);
	print_order_hexa(fmt, hexa_c);
	if (unsi_num != 0 || !fmt->dot || fmt->percision)
		free(hexa_c);
	return (fmt->print_len);
}
