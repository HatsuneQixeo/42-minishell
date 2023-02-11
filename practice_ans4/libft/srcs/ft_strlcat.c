/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:20:47 by ntan-wan          #+#    #+#             */
/*   Updated: 2022/07/11 15:20:48 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;
	size_t	src_remain;
	size_t	dst_len;
	size_t	new_dst_len;

	i = 0;
	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	new_dst_len = dst_len;
	if (dstsize <= dst_len)
		return (dstsize + src_len);
	while (src[i] && (new_dst_len + 1 < dstsize))
		dst[new_dst_len++] = src[i++];
	dst[new_dst_len] = '\0';
	src_remain = ft_strlen(&src[i]);
	return (new_dst_len + src_remain);
}
