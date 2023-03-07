/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:20:58 by hqixeo            #+#    #+#             */
/*   Updated: 2023/03/07 15:22:08 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*tokenizer_parse(char **src, const char *delimiters)
{
	const char	quote = (*src)[0];
	char	*ptr;
	char	*ret;

	ptr = &(*src)[-1];
	while (*++ptr != '\0' && !ft_strchr(delimiters, *ptr))
	{
		if (!ft_isquote(*ptr))
			continue ;
		ptr = ft_strchr(ptr + 1, *ptr);
	}
	ret = ft_substr((*src), 0, ptr - (*src));
	(*src) = ptr;
	return (ret);
}

/**
 * @brief Metacharacter lexer? Abandoned due to reading & as operator, including <& >&
 * Not my job to differenciate || and |
 * 	Maybe it is because of &&()
 * Or maybe I can just have another layer on top of all these <> bullshit
 * 	Stil can't because I'm not suppose to recognize & as an operator?
 * Might as well just make an error handling that is exclusively for & who cares
 * 	Imagine hard coding >& and <& and shits, no thx
 * (Another layer to recognise control operator, so & in >& would be interpreted as character?)
 * And take out )&( in ms_tokenizer? Might be doable
 * @param src "\t)&> <|(\n"
 * @return t_list* 
 */
t_list	*ms_tokenizer(const char *src)
{
	const char	*delimiters = ")&><|(";
	t_list		*lst;
	char		*end;
	char		*parse;

	if (src == NULL)
		return (NULL);
	lst = NULL;
	while (*src != '\0')
	{
		// src = ft_strskip_is(src, ft_isspace); // This propably is not doing anything
		end = ft_strskip_set(src, delimiters);
		if (end != src)
			ft_lstadd_back(&lst, ft_lstnew(
				token_new(ft_substr(src, 0, end - src), 1)));
		// end = ft_strskip_is(end, ft_isspace); // Do I need this?, for trimming the starting spaces, lexer probably is doing it already, but does can parser
		// // I might need to check whether an argument is actually given by ignoring space
		// if (*end == '\0') // I think I need some way to deal with this
		// 	break ;
		// else if (ft_strchr(delimiters, *end))
		// 	continue ;
		parse = tokenizer_parse(&end, delimiters);
		if (parse == NULL)
		{
			ft_lstclear(&lst, free);
			return (NULL);
		}
		ft_lstadd_back(&lst, ft_lstnew(token_new(parse, 0)));
		src = end;
	}
	return (lst);
}

// t_list	*ms_tokenizer(const char *src)
// {
// 	static const t_token	list[] = {
// 		{"<<", RDRT_HEREDOC},
// 		{">>", RDRT_APPEND},
// 		{"<", RDRT_INPUT},
// 		{">", RDRT_OVERWRITE},
// 		{"&&", CTRL_AND},
// 		{"||", CTRL_OR},
// 		{"(", SUBSH_BEGIN},
// 		{")", SUBSH_END},
// 		{"|", CTRL_PIPE},
// 	};
// 	t_list		*lst_token;
// 	char		*end;
// 	char		*parse;

// 	if (src == NULL)
// 		return (NULL);
// 	lst_token = NULL;
// 	while (*src != '\0')
// 	{
		
// 			ft_lstadd_back(&lst_token, ft_lstnew(
// 				token_new(ft_substr(src, 0, end - src), 1)));
// 		// end = ft_strskip_is(end, ft_isspace); // Do I need this?, for trimming the starting spaces, lexer probably is doing it already, but does can parser
// 		// // I might need to check whether an argument is actually given by ignoring space
// 		// if (*end == '\0') // I think I need some way to deal with this
// 		// 	break ;
// 		// else if (ft_strchr(delimiters, *end))
// 		// 	continue ;
// 		parse = tokenizer_parse(&end, delimiters);
// 		if (parse == NULL)
// 		{
// 			ft_lstclear(&lst_token, free);
// 			return (NULL);
// 		}
// 		ft_lstadd_back(&lst_token, ft_lstnew(token_new(parse, 0)));
// 		src = end;
// 	}
// 	return (lst);
// }
