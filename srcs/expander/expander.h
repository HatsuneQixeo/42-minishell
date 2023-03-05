/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:21:07 by hqixeo            #+#    #+#             */
/*   Updated: 2023/02/27 16:12:50 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "ms_common.h"
# include "token.h"

enum e_expandtoken
{
	LITERAL,
	EXPAND = 0b001,
	PARSE = 0b010,
	SPACE = 0b100
};

void	lstshow_expandtoken(void *content);
t_list	*expand_lexer(const char *arg);

char	*simpleexpand(char **envp, const char *arg);

char	*expand_var(char **envp, const char **p_it);
t_list	*expand_str(char **envp, const char *arg);

void	heredoc_expand(char **envp, t_list *lst);
char	**expand_lst_argv(char **envp, t_list *lst);

#endif
