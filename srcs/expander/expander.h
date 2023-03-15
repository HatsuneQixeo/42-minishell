/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:21:07 by hqixeo            #+#    #+#             */
/*   Updated: 2023/03/16 02:21:42 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "ms_common.h"
# include "token.h"

enum e_expandtoken
{
	LITERAL = 0b0000,
	EXPAND = 0b0001,
	PARSE = 0b0010,
	DELIMITER = 0b0100
};

void	lstshow_expandtoken(void *content);
t_list	*expd_tokenizer(const char *arg);

t_list	*wc_lexer(t_list *lst_token);
char	**wc_expand(t_list *lst_pattern);

void	expd_delimitertoken(t_list **lst);
void	expd_parse(t_list **lst);

char	*simpleexpand(char **envp, const char *arg);
char	*expand_var(char **envp, const char **p_it);
t_list	*expand_arg(char **envp, char *value);

char	**expand_lst_argv(char **envp, t_list *lst);

#endif
