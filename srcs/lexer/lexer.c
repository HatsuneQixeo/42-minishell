/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:21:06 by hqixeo            #+#    #+#             */
/*   Updated: 2023/02/27 16:12:49 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	lstshow_lexertoken(void *content)
{
	const t_token	*token = content;
	const char		*str_type;

	if (token->type == RDRT)
		str_type = CYAN"Redirect";
	else if (token->type == CTRL)
		str_type = YELLOW"Control";
	else if (token->type == SUBSH_BEGIN || token->type == SUBSH_END)
		str_type = MAGENTA"Subshell";
	else
		str_type = GREY"Default";
	ft_dprintf(2, "%s: %-8s: %b\n"DEF,
		lstname_token(NULL), str_type, token->value);
}

// int	find_tokenisstr(unsigned int i, const void *arr_token, const void *str)
// {
// 	const char	*value = ((const t_token *)arr_token)[i].value;

// 	return (cmp_strprefix(str, value));
// }

// static const size_t		length = (sizeof(operators) / sizeof(operators[0]));
// size_t	find = ft_arrfind(operators, length, find_tokenisstr, it);

// return (&operators[find]);

static const t_token	*tokentype(const char *it)
{
	static const t_token	operators[] = {
	{CTRL, "&&"},
	{CTRL, "||"},
	{CTRL, "|"},
	{RDRT, "<<"},
	{RDRT, ">>"},
	{RDRT, "<"},
	{RDRT, ">"},
	{SUBSH_BEGIN, "("},
	{SUBSH_END, ")"},
	{DEFAULT, ""}
	};
	unsigned int			i;

	i = 0;
	while (cmp_strprefix(it, operators[i].value))
		i++;
	return (&operators[i]);
}

static t_list	*lexer_lstnew_ifnempty(const char *src, const char *it)
{
	if (it == src)
		return (NULL);
	else
		return (ft_lstnew(token_new(ft_substr(src, 0, it - src), DEFAULT)));
}

t_list	*lexer_core(const char *input)
{
	t_list			*lst;
	const t_token	*token;
	const char		*it = input - 1;

	lst = NULL;
	while (*++it != '\0')
	{
		if (ft_isquote(*it))
			it = ft_strchr(it + 1, *it);
		token = tokentype(it);
		if (!ft_isspace(*it) && token->type == DEFAULT)
			continue ;
		ft_lstadd_back(&lst, lexer_lstnew_ifnempty(input, it));
		if (token->type != DEFAULT)
		{
			ft_lstadd_back(&lst, ft_lstnew(
					token_new(ft_strdup(token->value), token->type)));
			it += ft_strlen(token->value + 1);
		}
		input = it + 1;
	}
	ft_lstadd_back(&lst, lexer_lstnew_ifnempty(input, it));
	return (lst);
}

t_list	*ms_lexer(const char *raw)
{
	char	*input;
	t_list	*lst;

	input = ms_closequote(raw);
	if (input == NULL)
		return (NULL);
	add_history(input);
	lst = lexer_core(input);
	free(input);
	return (lst);
}
