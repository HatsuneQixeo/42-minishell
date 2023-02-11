/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:08:27 by ntan-wan          #+#    #+#             */
/*   Updated: 2022/07/11 15:10:04 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_words(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

char	*insert_word(char const *s, char c, int *j)
{
	char	*word;
	int		word_len;
	int		k;

	word_len = 0;
	k = 0;
	while (s[*j] && s[*j] != c)
	{
		word_len++;
		(*j)++;
	}	
	word = (char *)malloc(sizeof(char) * (word_len + 1));
	if (!word)
		return (NULL);
	while (word_len > 0)
		word[k++] = s[(*j) - word_len--];
	word[k] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	int		words;
	char	**result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	words = count_words(s, c);
	result = (char **)malloc(sizeof(char *) * (words + 1));
	if (!result)
		return (NULL);
	while (i < words)
	{
		while (s[j] && s[j] == c)
			j++;
		result[i] = insert_word(s, c, &j);
		i++;
	}
	result[i] = NULL;
	return (result);
}
