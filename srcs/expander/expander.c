/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:21:06 by hqixeo            #+#    #+#             */
/*   Updated: 2023/02/27 16:12:49 by hqixeo           ###   ########.fr       */
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

void	exp_expander(char **envp, t_list *lst_exptoken);
t_list	*exp_delimiter(t_list **lst);
t_list	*exp_parse(t_list **lst);

char	**expand_lst_argv(char **envp, t_list *lst)
{
	t_list	*lst_new;
	t_token	*token;

	lst_new = NULL;
	while (lst != NULL)
	{
		token = lst->content;
		// if (token->type != DEFAULT)
		// {
		// 	ms_errlog("Unknown token in expand_lst_argv");
		// 	lstshow_lexertoken(token);
		// }
		// else
		/* Future replacement for expand_str */
		{
			t_list	*lst_test = expand_lexer(token->value);

			exp_expander(envp, lst_test);
			lst_test = exp_delimiter(&lst_test);
			lst_test = exp_parse(&lst_test);
			ft_lstiter(lst_test, lstshow_expandtoken);
			ft_lstclear(&lst_test, del_token);
		}
			ft_lstadd_back(&lst_new, expand_str(envp, token->value));
		lst = lst->next;
	}
	return ((char **)ft_lsttoaa_clear(&lst_new));
}
