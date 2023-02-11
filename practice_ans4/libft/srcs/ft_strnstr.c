/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:35:59 by ntan-wan          #+#    #+#             */
/*   Updated: 2022/07/11 17:24:21 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = -1;
	if (!needle[0])
		return ((char *)haystack);
	while (haystack[++i] && i < len)
	{
		j = 0;
		if (haystack[i] == needle[j])
		{
			k = 0;
			while (needle[j] && (i + k < len))
			{
				if (haystack[i + k++] != needle[j])
					break ;
				j++;
			}
			if (needle[j] == '\0')
				return ((char *)haystack + i);
		}
	}
	return (NULL);
}
