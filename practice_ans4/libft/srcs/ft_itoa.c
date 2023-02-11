/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 13:16:26 by ntan-wan          #+#    #+#             */
/*   Updated: 2022/07/11 16:13:31 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_negative(int n, long *number_long)
{
	if (*number_long < 0)
	{
		*number_long = n;
		*number_long = -(*number_long);
		return (1);
	}
	else
		*number_long = n;
	return (0);
}

int	count_digit(long number)
{
	int	digit_sum;

	digit_sum = 0;
	if (number < 0)
	{
		digit_sum++;
		number = -number;
	}
	while (number > 0)
	{
		digit_sum++;
		number /= 10;
	}
	return (digit_sum);
}

char	*mem_alloc(char *ptr, long number_long, int digit)
{
	if (number_long == 0)
		ptr = ft_strdup("0");
	else if (number_long != 0)
		ptr = (char *)malloc(sizeof(char) * (digit + 1));
	return (ptr);
}

char	*get_char(char *result, int digit, long number_long, int negative)
{
	long	remainder;

	result[digit] = '\0';
	while (--digit)
	{	
		remainder = number_long % 10;
		result[digit] = remainder + '0';
		number_long /= 10;
	}
	if (negative)
		result[0] = '-';
	else
		result[0] = number_long + '0';
	return (result);
}

char	*ft_itoa(int n)
{
	long	number_long;
	int		digit;
	int		negative;
	char	*result;

	result = NULL;
	number_long = n;
	digit = count_digit(number_long);
	negative = is_negative(n, &number_long);
	result = mem_alloc(result, number_long, digit);
	if (!result)
		return (NULL);
	if (number_long != 0)
		result = get_char(result, digit, number_long, negative);
	return (result);
}
