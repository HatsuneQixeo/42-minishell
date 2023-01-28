/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_token_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 15:43:15 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/01/29 03:33:32 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#define DELIMITER " \t\r\v\f\n"

#include <stdio.h>

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

/* version 2 */

t_token_type	token_type_get2(char *token_value)
{
	int	token_len;

	token_len = ft_strlen(token_value);
	if (ft_strnstr(token_value, "|", token_len))
		return (TOKEN_PIPE);
	else if (ft_strnstr(token_value, "<<", token_len))
		return (TOKEN_HEREDOC);
	else if (ft_strnstr(token_value, ">>", token_len))
		return (TOKEN_APPEND);
	else if (ft_strnstr(token_value, ">", token_len))
		return (TOKEN_REDIR_OUT);
	else if (ft_strnstr(token_value, "<", token_len))
		return (TOKEN_REDIR_IN);
}

t_token	*token_create2(char *token_value)
{
	t_token	*token;
	
	token = ft_calloc(1, sizeof(t_token));
	token->value = token_value;
	token->type = token_type_get2(token_value);
	return (token);
}

t_token	**ms_tokens_arr_create2(char *input)
{
	int		i;
	char	*token_value;
	t_token	**tokens_arr;

	tokens_arr = ft_calloc((get_tokens_count(input) + 1), sizeof(t_token *));
	token_value = ms_strtok(input, DELIMITER);
	i = -1;
	while (token_value)
	{
		tokens_arr[++i] = token_create2(token_value);
		token_value = ms_strtok(NULL, DELIMITER);
	}
	return (tokens_arr);
}

void	ms_tokens_arr_free2(t_token ***tokens_arr)
{
	t_token **arr;

	int		i;
	arr = *tokens_arr;	
	if (!arr)
		return ;
	i = -1;
	while (arr[++i])
	{
		free(arr[i]->value);
		free(arr[i]);
	}
	free(arr);
	*tokens_arr = NULL;
}

/* version 3 */

// t_token	*token_create3(char *token_start, int token_len)
t_token	*token_create3(char *token_start, char *token_end)
{
	int		token_len;
	t_token	*new_token;

	token_len = token_end - token_start;
	new_token = (t_token *)malloc(1 * sizeof(t_token));
	new_token->value = malloc(sizeof(char) * token_len + 1);
	ft_strlcpy(new_token->value, token_start, token_len + 1);
	new_token->type = token_type_get2(new_token->value);
	return (new_token);
}

bool	is_space(char c)
{
	char	*spaces;

	spaces = " \t\r\v\f\n";
	while (*spaces)
	{
		if (*spaces == c)
			return (true);
		spaces++;
	}
	return (false);
}

bool	is_special_chars(char *input)
{
	int		i;
	char	*special_chars[7] = {"<", ">", "<<", ">>", "&&", "||", NULL};

	i = -1;
	while (special_chars[++i])
	{
		if (!ft_strncmp(input, special_chars[i], ft_strlen(special_chars[i])))
			return (true);
	}
	return (false);
}

t_list	*ms_tokenize(char *input)
{
	t_token	*token;
	int		token_len;
	t_list	*token_list;
	char	*token_start;

	token_list = NULL;
	token_start = input;
	if (!input)
		return (NULL);
	while (*input)
	{
		if (is_space(*input))
		{
			token_len = input - token_start;
			if (token_len)
			{
				token = token_create3(token_start, input);
				ft_lstadd_back(&token_list, ft_lstnew(token));
			}
			token_start += (token_len + 1);
		}
		else if (is_special_chars(input))
		{
			token_len = input - token_start;
			if (token_len)
			{
				token = token_create3(token_start, input);
				ft_lstadd_back(&token_list, ft_lstnew(token));
			}
			while (is_special_chars(input))
				input++;
			token_start += (token_len);
				token = token_create3(token_start, input);
				ft_lstadd_back(&token_list, ft_lstnew(token));
			while (is_special_chars(token_start))
				token_start++;
			if (!ft_isalpha(*token_start))
				token_start++;
		}
		input++;
	}
	if (*token_start)
		ft_lstadd_back(&token_list, ft_lstnew(token_create3(token_start, input)));
	return (token_list);
}

void	lst_print(void *token)
{
	t_token	*t;

	t = (t_token *)token;
	printf("value = (%s), type = %d\n", t->value, t->type);
}