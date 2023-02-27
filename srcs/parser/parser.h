/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 18:26:23 by hqixeo            #+#    #+#             */
/*   Updated: 2023/02/26 18:52:50 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "ms_common.h"
# include "ctrl.h"

int		heredoc_limiter(char *limiter);
t_list	*heredoc(const char *limiter);

int		parser_syntax(t_list *lst_token);

t_list	*ms_parser(t_list **lst_token);

#endif
