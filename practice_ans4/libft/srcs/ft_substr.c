/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:50:47 by ntan-wan          #+#    #+#             */
/*   Updated: 2022/07/11 16:00:01 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	s_len;
	size_t	ans_size;

	if (!s)
		return (NULL);
	ans_size = 0;
	s_len = ft_strlen(s);
	if (start < s_len)
		ans_size = s_len - start;
	if (len < ans_size)
		ans_size = len;
	result = (char *)malloc((ans_size + 1) * sizeof(char));
	if (!result)
		return (NULL);
	ft_strlcpy(result, s + start, ans_size + 1);
	return (result);
}
