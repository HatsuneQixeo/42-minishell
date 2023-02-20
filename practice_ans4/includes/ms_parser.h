/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 19:54:55 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/02/21 01:19:12 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_PARSER_H
# define MS_PARSER_H

# define SUCCESS 0
# define ERROR 1

# include "ms_ast.h"
# include "ms_token.h"
# include "ms_double_linked_list.h"

/* ms_parser */
void	ms_parser(t_double_list *token_list);
void	parse_token_list(t_double_list *token_list);
void	parse_token_type_reassign(t_double_list *token_list);
void	parse_token_concat_same_type(t_double_list *token_list);

/* parser_handler */
void	handle_quote(t_double_list *quote);
void	handle_variable(t_double_list *variable);
void	handle_backslash(t_double_list *backslash);
#endif