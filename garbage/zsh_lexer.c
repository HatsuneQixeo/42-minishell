/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zsh_lexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:20:58 by hqixeo            #+#    #+#             */
/*   Updated: 2023/02/25 10:20:58 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** This Lexer behaves the same way as the lexer in zsh
** , In a sense that every variable is getting expanded during parsing
** (after parsing might be a bit too much trouble than I want to deal with)
** (Although this itself is quite troublesome in it's own way)
**
** Let's say var="ho hi"
** So ec$var will be evaluated as "echo hi"
** Unlike the behavior in bash which will expand the value first and parse after
** which will result in "echo" "hi"
** , because the space in "ho hi" is not strung together
** Bash will behaves the same to ec"$var" however
** , because the space is strung in this case
*/

char	*lexer_quote(char **src);

// 

/// @brief 
/// Moves the ptr pointer to the end of the {varname}
/// , and src pointer in front of it by 1
/// @param src The address of the pointer to the 
/// @param ptr The address of the pointer to the '$' character
/// @return A linked list with the previous element and the variable
char	*ms_env(char **src, char **ptr)
{
	char	*var;

	var = ft_strcombine(ft_substr(*src, 0, *ptr - *src), expander_node(ptr));
	*src = *ptr + 1;
	return (var);
};

static char	*lexer_buffer(char **src)
{
	t_list	*buffer;
	char	*ptr;

	buffer = NULL;
	ptr = *src - 1;
	while (*++ptr != '\0' && !ft_isspace(*ptr))
	{
		if (*ptr == '\\')
			shell_backslash(ptr);
		else if (*ptr == '\'' || *ptr == '\"')
		{
			ft_lstadd_back(&buffer, ft_lstnew(ft_substr(*src, 0, ptr - *src)));
			char	*parse = lexer_quote(&ptr);

			if (parse == NULL)
			{
				ft_lstclear(&buffer, free);
				return (NULL);
			}
			ft_lstadd_back(&buffer, ft_lstnew(parse));
			*src = ptr + 1;
		}
		else if (*ptr == '$')
		{
			ft_lstadd_back(&buffer, ft_lstnew(ft_substr(*src, 0, ptr - *src)));
			ft_lstadd_back(&buffer, ft_lstnew(expander_node(&ptr)));
			*src = ptr + 1;
		}
	}
	ft_lstadd_back(&buffer, ft_lstnew(ft_substr(*src, 0, ptr - *src)));
	*src = ptr;
	return (ft_lsttostr_clear(&buffer));
}

static char	**lexer_core(char *src)
{
	t_list	*lst;
	char	*arg;

	lst = NULL; 
	src--;
	while (*++src != '\0')
	{
		if (ft_isspace(*src))
			continue ;
		arg = lexer_buffer(&src);
		if (arg == NULL)
		{
			ft_lstclear(&lst, free);
			return (NULL);
		}
		ft_lstadd_back(&lst, ft_lstnew(arg));
		if (*src == '\0')
			break ;
	}
	// ft_lstiter(lst, lstshow_str);
	return (ft_lsttoaa_clear(&lst));
}

char	**ms_lexer(const char *src)
{
	char	*dup;
	char	**strlist;

	dup = ft_strdup(src);
	strlist = lexer_core(dup);
	free(dup);
	return (strlist);
}
