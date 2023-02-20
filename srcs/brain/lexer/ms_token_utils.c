/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_token_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 15:43:15 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/02/20 22:39:18 by ntan-wan         ###   ########.fr       */
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

/* version 2 */

static bool	is_word(char c)
{
	return (ft_isalpha(c));
}

static bool	is_space(char c)
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

static bool	is_special_chars(char c)
{
	return (!ft_isalpha(c) && !is_space(c));
}

static void	move_input_ptr_to_end_of_a_word(char **input)
{
	if (is_word(**input))
	{
		while (**input && is_word(**input) || **input && **input == '.')
			(*input)++;
	}
	else if (**input == '-' || **input == '.')
	{
		while (**input && !is_space(**input))
			(*input)++;
	}
	else
	{
		while (**input && is_special_chars(**input))
			(*input)++;
	}
}

t_list	*ms_tokenize(char *input)
{
	t_list	*token_list;
	char	*token_value;
	char	*input_start;

	token_list = NULL;
	input_start = input;
	while (*input)
	{
		if (is_word(*input) || is_special_chars(*input))
		{
			move_input_ptr_to_end_of_a_word(&input);
			token_value = token_value_get(input_start, input);
			ft_lstadd_back(&token_list, ft_lstnew(token_init(token_value)));
			input_start += (input - input_start);
		}
		else
		{
			input_start++;
			input++;
		}
	}
	return (token_list);
}

/* version 3 */

const t_token_type_grammar	*token_type_grammar_get(char c)
{
	const t_token_type_grammar	grammar[] = {
	{"&", AMPERSAND}, {"|", OR}, {";", TOKEN_SEP_SEIMICOLON},
	{"<", TOKEN_REDIR_IN}, {">", TOKEN_REDIR_OUT}, {0,0},
	};
	
	return (grammar);
}

void	ms_tokenize3(char *input)
{
	char	*value;

	value = ft_strdup(input);
	

}
