/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 15:17:22 by ntan-wan          #+#    #+#             */
/*   Updated: 2022/08/09 21:13:12 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include "../includes/libft.h"

/*
   Only concerns with <width>, <percision> and <negative> flags only.

   unsigned long long vs unsigned long :
   Memory addresses are 32-bits(unsigned long) long on most CPU today. However
   there is a increasing trend toward 64-bit(unsigned long long) addressing.
   Therefore it is safer to use unsigned long long data type to store memory
   address.
   
   ft_ptr_len vs ft_num_len :
   ft_num_len only accept unsigned int data type as input. I'm passing
   unsigned long long data type here, thus I created another function for it.

   and_negative_flag_ptr :
   This function deals with situation when negative flag is raised.

   convert_ptr :
   This function converts number to pointer format(hexadecimal).
   I prefixed my character 'array' with "0x", and fill up the rest of the
   'slots' with the correct characters.
   I move my pointer to character 'array' up by 2 when I don't want 
   to print out the prefix, "0x". For example :

   |0|x|1|2|3|
    ^
    |

    |0|x|1|2|3|
         ^
	 |

   The only situation when I don't want to print out the prefix is when
   <percision> > ptr_c_len - 2(minus out the prefix "0x") as I will print out 
   the prefix using print_prefix_ptr.

   print_prefix_ptr :
   This function print out prefix accordingly. 
   When <percision> > ptr_c_len - 2(minus out the prefix "0x"), '0' will
   fill up addtional slots. For example :
   ("%.3p", 10) -> 0x00a
   The printing order is : "0x" -> "00" -> "a"
   
   and_negative_flag_ptr :
   This function handles the printing order.
   1. If <negative> flag is raised:
      'spaces' are printed after number characters.
   2. If <negative> flag is not raised:
      'spaces' are printed before number characters. 

   (listed in print_space.c)
   print_space :
   Print spaces accordingly. Duhhh

   print_ptr :
   The core function.
*/

int	ft_ptr_len(unsigned long long num, int base)
{
	int	len;

	len = 0;
	if (num == 0)
		len++;
	while (num > 0)
	{
		len++;
		num /= base;
	}
	return (len);
}

char	*convert_ptr(unsigned long long ptr)
{
	int		ptr_len;
	char	*ptr_c;
	char	*base;

	base = "0123456789abcdef";
	ptr_len = ft_ptr_len(ptr, 16);
	ptr_c = (char *)malloc(sizeof(char) * (2 + ptr_len + 1));
	if (!ptr_c)
		return (0);
	if (ptr == 0)
		ptr_c[2] = '0';
	ptr_c[0] = '0';
	ptr_c[1] = 'x';
	ptr_c[2 + ptr_len] = '\0';
	while (ptr != 0)
	{
		ptr_c[2 + ptr_len - 1] = base[ptr % 16];
		ptr /= 16;
		ptr_len--;
	}
	return (ptr_c);
}

void	print_prefix_ptr(t_fmt *fmt, char *ptr_c)
{
	int	ptr_c_len;
	int	space_count;

	ptr_c_len = ft_strlen(ptr_c);
	if (fmt->percision > (ptr_c_len - 2))
	{
		write(1, "0x", 2);
		space_count = fmt->percision - (ptr_c_len - 2);
		while (space_count--)
			fmt->print_len += write(1, "0", 1);
	}
}

void	and_negative_flag_ptr(t_fmt *fmt, char *ptr_c)
{
	int	space_count;
	int	ptr_c_len;

	ptr_c_len = ft_strlen(ptr_c);
	space_count = fmt->width - fmt->print_len;
	if (fmt->width > 0)
		fmt->print_len = fmt->width;
	if (fmt->negative)
	{
		ft_putstr_fd(ptr_c, 1);
		print_space(fmt, space_count);
	}
	else
	{
		print_space(fmt, space_count);
		if (!(fmt->percision > (ptr_c_len - 2)))
			ft_putstr_fd(ptr_c, 1);
		else
			ft_putstr_fd(ptr_c + 2, 1);
	}
}

int	print_ptr(t_fmt *fmt, unsigned long long ptr)
{
	char	*ptr_c;

	ptr_c = convert_ptr(ptr);
	print_prefix_ptr(fmt, ptr_c);
	fmt->print_len += ft_strlen(ptr_c);
	if (fmt->dot || (fmt->width > (int)ft_strlen(ptr_c)))
		and_negative_flag_ptr(fmt, ptr_c);
	else
		ft_putstr_fd(ptr_c, 1);
	free(ptr_c);
	return (fmt->print_len);
}
