/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:21:07 by hqixeo            #+#    #+#             */
/*   Updated: 2023/02/26 18:52:49 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "ms_common.h"
# include "token.h"

char	*ft_getenv(char **envp, const char *varname);
char	*expand_var(char **envp, const char **p_it);
t_list	*expand_str(char **envp, const char *arg);

void	heredoc_expand(char **envp, t_list *lst);
char	**expand_lst_argv(char **envp, t_list *lst);
#endif
