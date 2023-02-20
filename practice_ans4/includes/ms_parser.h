/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 19:54:55 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/02/20 23:33:38 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_PARSER_H
# define MS_PARSER_H

# define SUCCESS 0
# define ERROR 1

# include "ms_token.h"
# include "ms_double_linked_list.h"
# include "ms_ast.h"

void	ms_parser(t_double_list *token_list);
void	parse_token_list(t_double_list *token_list);
#endif