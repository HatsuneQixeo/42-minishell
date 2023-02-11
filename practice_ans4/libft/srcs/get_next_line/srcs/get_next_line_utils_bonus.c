/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 16:33:24 by ntan-wan          #+#    #+#             */
/*   Updated: 2022/10/20 11:07:12 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	contain_newline(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*join_strs(const char *str1, const char *str2)
{
	char	*str;
	int		len;
	int		i;

	len = 0;
	if (!str1 && !str2)
		return (NULL);
	while (str1 && str1[len])
		len++;
	i = 0;
	while (str2 && str2[i])
		i++;
	str = malloc_zero(len + i + 1, sizeof(str));
	if (!str)
		return (NULL);
	len = -1;
	while (str1 && str1[++len])
		str[len] = str1[len];
	i = -1;
	while (str2 && str2[++i])
		str[len + i] = str2[i];
	return (str);
}

char	*t_strdup(const char *str1)
{
	char	*str2;
	int		i;

	if (!str1)
		return (t_strdup(""));
	i = 0;
	while (str1[i])
		i++;
	str2 = malloc_zero(i + 1, sizeof(str2));
	if (!str2)
		return (NULL);
	i = 0;
	while (str1[i])
	{
		str2[i] = str1[i];
		i++;
	}
	return (str2);
}

void	*malloc_zero(size_t count, size_t size)
{
	size_t			total;
	void			*ptr;
	unsigned char	*c;

	total = count * size;
	ptr = malloc(total);
	if (!ptr)
		return (NULL);
	c = (unsigned char *)ptr;
	while (total != 0)
	{
		*c = '\0';
		c++;
		total--;
	}
	return (ptr);
}

void	free_strs(char **str, char **str2, char **str3)
{
	if (str && *str)
	{
		free(*str);
		*str = NULL;
	}
	if (str2 && *str2)
	{
		free(*str2);
		*str2 = NULL;
	}
	if (str3 && *str3)
	{
		free(*str3);
		*str3 = NULL;
	}
}
