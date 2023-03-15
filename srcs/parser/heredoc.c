/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:21:06 by hqixeo            #+#    #+#             */
/*   Updated: 2023/03/16 02:21:41 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* Return 0 is given limiter has no quote, 1 if has quote */
static int	heredoc_limiter(char *limiter)
{
	int	hasquote;

	hasquote = 0;
	while (*limiter != '\0')
	{
		if (!ft_isquote(*limiter))
		{
			limiter++;
			continue ;
		}
		ft_memmove(limiter, limiter + 1, ft_strlen(limiter + 1) + 1);
		hasquote = 1;
	}
	return (hasquote);
}

static char	*heredoc(const char *limiter)
{
	t_list	*lst_buffer;
	char	*input;

	lst_buffer = NULL;
	while (1)
	{
		input = readline("heredoc> ");
		if (input == NULL || !ft_strcmp(limiter, input))
			break ;
		ft_lstadd_back(&lst_buffer, ft_lstnew(input));
	}
	free(input);
	return (ft_lsttostr_delimiter_clear(&lst_buffer, "\n"));
}

static int	heretoken(t_token *token_operator, t_token *token_arg)
{
	char	*herestr;

	if (heredoc_limiter(token_arg->value))
	{
		free(token_operator->value);
		token_operator->value = ft_strdup("\"<<\"");
	}
	herestr = heredoc(token_arg->value);
	if (herestr == NULL)
		return (-1);
	free(token_arg->value);
	token_arg->value = herestr;
	return (0);
}

int	ms_heredoc(t_list *lst_token)
{
	t_token	*token;

	while (lst_token != NULL)
	{
		token = lst_token->content;
		lst_token = lst_token->next;
		if (!(token->type == RDRT && rdrt_getft(token->value) == rdrt_heredoc))
			continue ;
		if (heretoken(token, lst_token->content) == -1)
			return (-1);
		lst_token = lst_token->next;
	}
	return (0);
}
