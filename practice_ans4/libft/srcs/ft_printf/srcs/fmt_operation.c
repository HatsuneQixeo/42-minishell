/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmt_operation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 19:10:42 by ntan-wan          #+#    #+#             */
/*   Updated: 2022/07/20 21:53:49 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
  Used va_arg() function to point to the next variadic arguments and pass it
  into the functions accordingly.
*/

int	fmt_operation(t_fmt *fmt, va_list args)
{
	int	print_len;

	print_len = 0;
	if (fmt->c)
		print_len += print_c(fmt, va_arg(args, int));
	else if (fmt->str)
		print_len += print_s(fmt, va_arg(args, char *));
	else if (fmt->ptr)
		print_len += print_ptr(fmt, va_arg(args, unsigned long long));
	else if (fmt->decimal || fmt->integer)
		print_len += print_decimal(fmt, va_arg(args, int));
	else if (fmt->unsi)
		print_len += print_unsi(fmt, va_arg(args, unsigned int));
	else if (fmt->hexa_lower || fmt->hexa_upper)
		print_len += print_hexa(fmt, va_arg(args, unsigned int));
	else if (fmt->percent)
		print_len += print_percent(fmt);
	return (print_len);
}
