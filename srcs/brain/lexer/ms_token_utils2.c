/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_token_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:04:28 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/01/30 17:29:26 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

char	*token_value_get(char *token_start, char *token_end)
{
	int		token_len;
	char	*token_value;

	token_value = NULL;
	token_len = token_end - token_start;
	if (token_len)
	{
		token_value = malloc(sizeof(char) * token_len + 1);
		ft_strlcpy(token_value, token_start, token_len + 1);
	}
	return (token_value);
}

t_token_type	token_type_get(char *token_value)
{
	int								i;
	int								token_len;
	const t_token_type_key_value	special_token_types[] = {
	{"<", TOKEN_REDIR_IN},
	{">", TOKEN_REDIR_OUT},
	{"<<", TOKEN_HEREDOC},
	{">>", TOKEN_APPEND},
	{"|", TOKEN_PIPE},
	{"||", TOKEN_OR},
	{"&&", TOKEN_AND},
	};

	token_len = ft_strlen(token_value);
	i = -1;
	if (*token_value == '-')
		return (TOKEN_OPTION);
	else if (ft_isalpha(*token_value) || *token_value == '.')
		return (TOKEN_WORD);
	while (++i < sizeof(special_token_types) / sizeof(special_token_types[i]))
	{
		if (!ft_strncmp(token_value, special_token_types[i].key, token_len))
			return (special_token_types[i].value);
	}
	return (TOKEN_UNKNOWN);
}

t_token	*token_init(char *token_value)
{
	t_token	*token;

	if (!token_value)
		return (NULL);
	token = ft_calloc(1, sizeof(t_token));
	token->value = token_value;
	token->type = token_type_get(token_value);
	return (token);
}

void	token_free(void *token)
{
	t_token	*t;

	t = (t_token *)token;
	free(t->value);
	free(t);
}

void	token_list_free(t_list	**token_list)
{
	ft_lstclear(token_list, token_free);
}
