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

# include "ms_common.h"
# include "parser.h"
# include "interpretor.h"

/* routine */
char	*ms_closequote(const char *raw);
/* Lexer */
t_list	*ms_lexer(const char *input_raw);

#endif
