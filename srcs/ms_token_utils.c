/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_token_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 17:31:41 by ntan-wan          #+#    #+#             */
/*   Updated: 2022/12/26 18:22:30 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

static bool	is_space_or_endline(char c)
{
	return (!c || c >= 9 && c <= 13 || c == ' ');
}

t_token	*token_init(char *token_start, char *token_end)
{
	int		token_len;
	t_token	*new_token;

	new_token = NULL;
	token_len = token_end - token_start;
	new_token = malloc(sizeof(t_token));
	new_token->type = UNKNOWN;
	ft_strlcpy(new_token->value, token_start, token_len + 1);
	new_token->next = NULL;
	return (new_token);
}

// void	set_token_type

void	token_add(t_list **head, t_token *token)
{
	ft_lstadd_back(head, ft_lstnew(token));
}

t_list	*ms_tokenize(char *input)
{
	int		i;
	t_list	*tokens;
	int		input_len;
	int		token_length;
	char	*token_start;

	i = -1;
	tokens = NULL;
	token_length = 0;
	token_start = input;
	input_len = ft_strlen(input);
	while (++i < input_len + 1)
	{
		if (is_space_or_endline(*input))
		{
			token_length = input - token_start;
			if (token_length)
				token_add(&tokens, token_init(token_start, input));
			token_start = input + 1;
		}
		input++;
	}
	return (tokens);
}

void	ms_tokens_free(t_list **tokens)
{
	ft_lstclear(tokens, free);
}

/* ------------------------------------------------------------------ */

void	ms_token_value_print(void *tokens)
{
	t_token	*t;
	
	t = (t_token *)tokens;
	printf("%s\n", t->value);
}

void	ms_token_list_value_print(t_list *tokens)
{
	ft_lstiter(tokens, ms_token_value_print);
}