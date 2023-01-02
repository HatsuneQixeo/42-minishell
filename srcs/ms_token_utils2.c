/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_token_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 15:43:15 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/01/02 13:38:03 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static char	*last_token_create(char *token_start)
{
	return (ft_strdup(token_start));
}

size_t	get_size(void *ptr)
{
	if (!ptr)
		return (0);
	size_t	size = 0;
	char *c_ptr = (char *)ptr;
	for (int i = 0; c_ptr[i] != '\0'; i++)
		size++;
	// printf("%ld\n", size);
	return (size);
}

/*void    *my_memcpy(void *dest, const void *src, size_t n)
{
        size_t  i;

        i = 0;
        if (!dest && !src)
                return (NULL);
		// printf("%ld\n", n);
        while (i < n)
        {
			    // printf("%c|", ((unsigned char *)src)[i]);
                ((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
                i++;
        }
		// printf("%s\n", (char *)dest);
        return (dest);
}*/
// void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
void	*ft_realloc(void *ptr, size_t new_size)
{
	void	*new_ptr;
	
	if (!ptr)
		return (malloc(new_size));
	else if (!new_size)
		return (free(ptr), NULL);
	char **c_ptr;

	c_ptr = (char **)ptr;
	int i = -1;
	while (c_ptr[++i]);
		printf("size %d\n", i);
	// size_t size = sizeof(c_ptr) / sizeof(c_ptr[0]);
	// if (c_ptr)
		// printf("%ld\n", size);
		// printf("%s\n", c_ptr[0]);
	new_ptr = malloc(new_size);
	if (new_ptr)
		ft_memcpy(new_ptr, ptr, (i + 1) * sizeof(char *));
	((unsigned char **)new_ptr)[i] = "\0";
		// my_memcpy(new_ptr, ptr, old_size);
		// my_memcpy(new_ptr, ptr, get_size(ptr));
	// printf("%ld\n", sizeof((char **)ptr)/sizeof(((char **)ptr)[0]));
	 	// printf("%ld\n", sizeof());
	free(ptr);
	return (new_ptr);
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
	return (last_token_create(token_start));
}

int	get_tokens_count(char *input)
{
	int		count;
	char	*token;

	count = 0;
	token = ms_strtok(input, " ");
	while (token)
	{
		count++;
		token = ms_strtok(NULL, " ");
	}
	// printf("%d\n", count);
	return (count);
}

char	**tokens_array_create(char *input)
{	
	int		i;
	int		count;
	char	*token;
	char	**tokens_arr;

	count = get_tokens_count(input);
	tokens_arr = NULL;
	tokens_arr = malloc(sizeof(count + 1) * sizeof(char *));
	tokens_arr[count] = "";
	token = ms_strtok(input, " ");
	i = -1;
	// count = 0;
	while (token)
	{
		// printf("%s\n", token);
		tokens_arr[++i] = token;
		// printf("%s\n", tokens_arr[i]);
		// tokens_arr = ft_realloc(tokens_arr, count * sizeof(char *), ++count * sizeof(char *));
		// tokens_arr[count - 1] = token;
	// 	// printf("%s\n", tokens_arr[count -1]);
	// 	// printf("%d\n", count);
		token = ms_strtok(NULL, " ");
	}
	// tokens_arr[] = "\0";
	return (tokens_arr);
}

char	**tokens_array_create2(char *input)
{	
	// int		i;
	int		count;
	char	*token;
	char	**tokens_arr;

	// count = get_tokens_count(input);
	tokens_arr = NULL;
	// tokens_arr = malloc(sizeof(count + 1) * sizeof(char *));
	// tokens_arr[count] = "";
	token = ms_strtok(input, " ");
	// i = -1;
	count = 0;
	while (token)
	{
		// printf("%s\n", token);
		// tokens_arr[++i] = token;
		// printf("%s\n", tokens_arr[i]);
		tokens_arr = ft_realloc(tokens_arr, (++count + 1) * sizeof(char *));
		// tokens_arr[count] = "\0";
		tokens_arr[count - 1] = token;
		// printf("%s\n", tokens_arr[count -1]);
	// 	// printf("%d\n", count);
		token = ms_strtok(NULL, " ");
	}
	// tokens_arr[] = "\0";
	return (tokens_arr);
}