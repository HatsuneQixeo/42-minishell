/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 17:59:45 by ntan-wan          #+#    #+#             */
/*   Updated: 2022/08/09 21:14:08 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include "../includes/libft.h"

/*
   calc_unsi_num_len :
   Count number of digits in order to allocate appropriate memory to it.
   
   ft_uitoa :
   Created uitoa instead of using itoa because itoa only has int data 
   type parameter. If the number exceed the range of int, itoa will not 
   convert unsigned number into the right number in int data type context.

   Place character from the end of the 'array' first, gradually
   moving to the start of the 'array'. "% 10" is used to get the remainder,
   i.e, get the last digit of the number first. Example :
   13 -> | |3|
      -> |1|3|
  
   flags_unsi :
   Handles flags accordingly.

   print_order_unsi :
   Handle the printing order.
*/

int	calc_unsi_num_len(unsigned int num, int base)
{
	int	len;

	len = 0;
	if (num == 0)
		len++;
	while (num != 0)
	{
		len++;
		num /= base;
	}
	return (len);
}

char	*ft_uitoa(unsigned int n)
{
	char	*num;
	int		len;

	len = calc_unsi_num_len(n, 10);
	num = (char *)malloc(sizeof(char) * (len + 1));
	if (!num)
		return (0);
	if (n == 0)
		num[0] = '0';
	num[len] = '\0';
	while (n != 0)
	{
		num[len - 1] = n % 10 + '0';
		n = n / 10;
		len--;
	}
	return (num);
}

void	flags_unsi(t_fmt *fmt, int unsi_num_len, int unsi_num_c_len)
{
	if (fmt->percision > unsi_num_c_len)
		fmt->pad = fmt->percision - unsi_num_c_len;
	if (fmt->width > fmt->pad + unsi_num_len)
		fmt->offset = fmt->width - fmt->pad - unsi_num_len;
	if ((fmt->space || fmt->plus) && ++fmt->print_len && fmt->offset)
		--fmt->offset;
	fmt->print_len += fmt->offset + fmt->pad + unsi_num_len;
	if (fmt->zero && !fmt->dot)
	{
		fmt->pad = fmt->offset;
		fmt->offset = 0;
	}
}

void	print_order_unsi(t_fmt *fmt, char *unsi_num_c)
{
	if (fmt->negative)
	{
		print_prefix_unsi(fmt, unsi_num_c);
		while (fmt->offset--)
			ft_putchar_fd(' ', 1);
	}
	else
	{
		while (fmt->offset--)
			ft_putchar_fd(' ', 1);
		print_prefix_unsi(fmt, unsi_num_c);
	}
}

int	print_unsi(t_fmt *fmt, unsigned int unsi_num)
{
	int		unsi_num_len;
	char	*unsi_num_c;
	int		unsi_num_c_len;

	unsi_num_len = 0;
	unsi_num_c = "";
	if (unsi_num != 0 || !fmt->dot || fmt->percision)
	{
		unsi_num_len = calc_unsi_num_len(unsi_num, 10);
		unsi_num_c = ft_uitoa(unsi_num);
	}
	unsi_num_c_len = (int)ft_strlen(unsi_num_c);
	flags_unsi(fmt, unsi_num_len, unsi_num_c_len);
	print_order_unsi(fmt, unsi_num_c);
	if (unsi_num != 0 || !fmt->dot || fmt->percision)
		free(unsi_num_c);
	return (fmt->print_len);
}
