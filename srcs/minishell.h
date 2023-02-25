/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 17:11:38 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/02/25 10:21:08 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>

# include <readline/readline.h>
# include <readline/history.h>

# include "ms_common.h"
# include "token.h"
# include "rdrt.h"
# include "ctrl.h"
# include "expander.h"

/* routine */
void	ms_input(char **envp);
char	*ms_closequote(const char *raw);
/* Lexer */
t_list	*ms_lexer(const char *input_raw);

/* Control Structure*/
t_list	*ms_control_structure(const char *input_raw);
t_list	*ms_control_token(const char *input_raw);

/* Parser */
char	*parser_heredoc(char **envp, char *limiter);
int		parser_syntax(t_list *lst_token);
t_list	*ms_parser(t_list **lst_token);

/* Exe */
void	ms_interpretor(t_data *data, t_list **lst_ctrl);

#endif
