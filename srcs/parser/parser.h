/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 18:26:23 by hqixeo            #+#    #+#             */
/*   Updated: 2023/03/16 02:21:42 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "ms_common.h"
# include "ctrl.h"

int		parse_default(t_ctrl *ctrl, t_list **lst_token, t_ftctrl *condition);
int		parse_rdrt(t_ctrl *ctrl, t_list **lst_token, t_ftctrl *condition);
int		parse_ctrl(t_ctrl *ctrl, t_list **lst_token, t_ftctrl *condition);
int		parse_subshbegin(t_ctrl *ctrl, t_list **lst_token, t_ftctrl *condition);
int		parse_subshend(t_ctrl *ctrl, t_list **lst_token, t_ftctrl *condition);

int		parser_syntax(t_list *lst_token);
int		ms_heredoc(t_list *lst_token);

t_list	*ms_parser(t_list **lst_token);

#endif
