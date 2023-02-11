/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 14:48:28 by ntan-wan          #+#    #+#             */
/*   Updated: 2022/07/11 14:50:59 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char	*d;
	char	*s;
	int		i;

	d = (char *)dst;
	s = (char *)src;
	if (dst == src)
		return (dst);
	else if (s < d)
	{
		i = (int)n - 1;
		while (i >= 0)
		{
			*(d + i) = *(s + i);
			i--;
		}
		return (dst);
	}
	else
	{
		i = -1;
		while (++i < (int)n)
			*d++ = *s++;
		return (dst);
	}	
}
