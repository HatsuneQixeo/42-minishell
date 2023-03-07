/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:21:06 by hqixeo            #+#    #+#             */
/*   Updated: 2023/03/07 15:22:16 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*simpleexpand(char **envp, const char *arg)
{
	const char	*var = ft_strchr(arg, '$');
	t_list		*lst_buffer;

	lst_buffer = NULL;
	while (var != NULL)
	{
		if (var != arg)
			ft_lstadd_back(&lst_buffer, ft_lstnew(ft_substr(arg, 0, var - arg)));
		ft_lstadd_back(&lst_buffer, ft_lstnew(expand_var(envp, &var)));
		arg = var + 1;
		var = ft_strchr(arg, '$');
	}
	if (var != arg)
		ft_lstadd_back(&lst_buffer, ft_lstnew(ft_strdup(arg)));
	return (ft_lsttostr_clear(&lst_buffer));
}

void	heredoc_expand(char **envp, t_list *lst)
{
	while (lst != NULL)
	{
		lst->content = ft_strmodify(strmod_replace, lst->content,
				simpleexpand(envp, lst->content));
		lst = lst->next;
	}
}

void	bash_shenanigan(char *str)
{
	while (*str != '\0')
	{
		if (*str == '$' && ft_isquote(*(str + 1)))
			ft_memmove(str, str + 1, ft_strlen(str + 1) + 1);
		if (ft_isquote(*str))
			str = ft_strchr(str + 1, *str);
		str++;
	}
}

t_list	*expand_arg(char **envp, const char *value)
{
	t_list	*lst_test;

	/*
		I think I should try to remove all the $'' before anything starts,
		($'' || $"") -> ('' || "")
		Gonna have to hardcode it,
		not gonna looks pretty,
		but I ain't got no other way
	*/
	char	*dupvalue = ft_strdup(value);
	bash_shenanigan(dupvalue);
	lst_test = expd_tokenizer(dupvalue);
	expd_expand(envp, lst_test);
	expd_delimitertoken(&lst_test);
	lst_test = expd_parse(&lst_test);
	free(dupvalue);
	return (lst_test);
}

char	**expand_lst_argv(char **envp, t_list *lst)
{
	t_list	*lst_new;
	t_token	*token;

	lst_new = NULL;
	while (lst != NULL)
	{
		token = lst->content;
		/*
			Consider changing this after let's say,
			parser add string instead of token
		*/
		ft_lstadd_back(&lst_new, expand_arg(envp, token->value));
		lst = lst->next;
	}
	return ((char **)ft_lsttoaa_clear(&lst_new));
}
