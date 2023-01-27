/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_token_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 15:43:15 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/01/27 14:29:08 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#define DELIMITER " \t\r\v\f\n"

static bool	is_delimiter(char c, char *delimiter)
{
	while (*delimiter)
	{
		if (c == *delimiter)
			return (true);
		delimiter++;
	}
	return (false);
}

static char	*token_create(char *token_start, char *token_end)
{
	int		token_len;
	char	*new_token;

	new_token = "";
	token_len = token_end - token_start;
	new_token = malloc(sizeof(char) * token_len + 1);
	ft_strlcpy(new_token, token_start, token_len + 1);
	return (new_token);
}

/* 
	@brief  strtok = string token.
	@note	Split a string into tokens based on specified delimiters.
	@note	To get subsequent tokens, call 'strktok' again and pass 'NULL'
			as first argument.
	@retval Returns a single token.
	@retval Returns NULL when there are no more tokens left.
 */
char	*ms_strtok(char *str, char *delimiter)
{
	int			token_len;
	char		*token_start;
	static char	*saved_str;

	if (str)
		saved_str = str;
	else if (!saved_str)
		return (NULL);
	token_start = saved_str;
	while (*saved_str)
	{
		if (is_delimiter(*saved_str, delimiter))
		{
			token_len = saved_str - token_start;
			if (token_len)
				return (token_create(token_start, saved_str));
			token_start++;
		}
		saved_str++;
	}
	saved_str = NULL;
	return (ft_strdup(token_start));
}

static int	get_tokens_count(char *input)
{
	int		count;
	char	*token;

	count = 0;
	token = ms_strtok(input, DELIMITER);
	while (token)
	{
		count++;
		free(token);
		token = ms_strtok(NULL, DELIMITER);
	}
	return (count);
}

char	**ms_tokens_arr_create(char *input)
{	
	int		i;
	int		count;
	char	*token;
	char	**tokens_arr;

	count = get_tokens_count(input);
	tokens_arr = malloc((count + 1) * sizeof(char *));
	token = ms_strtok(input, DELIMITER);
	i = -1;
	while (token)
	{
		tokens_arr[++i] = token;
		token = ms_strtok(NULL, DELIMITER);
	}
	tokens_arr[count] = 0;
	return (tokens_arr);
}

void	ms_tokens_arr_free(char ***tokens_arr)
{
	int		i;
	char	**arr;

	arr = *tokens_arr;
	if (!arr)
		return ;
	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
	*tokens_arr = NULL;
}
