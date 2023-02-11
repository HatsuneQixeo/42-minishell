/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 17:41:18 by ntan-wan          #+#    #+#             */
/*   Updated: 2022/08/09 21:11:21 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include "../includes/libft.h"

/* 
   This function iterates each chracter in a string. If character '%' not found,
   it will print out the input character and return printed length accordingly.

   If '%' is found, we will check the characters between '%' 
   and "c/s/p/d/i/u/x/X/%".

   fmt_update_flags will process the in-between characters. It will check which
   flags are being raised and store this info in struct t_fmt.

   fmt_update will store "c/s/p/d/i/u/x/X/%" in struct t_fmt instead.

   fmt_operation will carry out actions accordingly to the infos stored in
   struct t_fmt.
*/

int	put_c(char c)
{
	return (write(1, &c, 1));
}

int	fmt_process(const char **str, va_list args)
{
	t_fmt	fmt;
	int		print_len;

	fmt_init(&fmt);
	while (**str && !ft_strchr("cspdiuxX%", **str))
	{
		fmt_update_flags(**str, &fmt);
		(*str)++;
	}
	fmt_update(**str, &fmt);
	print_len = fmt_operation(&fmt, args);
	return (print_len);
}

int	ft_printf(const char *str, ...)
{	
	va_list	args;
	int		print_len;

	print_len = 0;
	va_start(args, str);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			print_len += fmt_process(&str, args);
		}
		else
			print_len += put_c(*str);
		str++;
	}
	va_end(args);
	return (print_len);
}
