/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_ast.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 22:10:12 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/02/13 22:25:12 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_AST_H
# define MS_AST_H

# include "ms_btree.h"
# include "ms_token.h"
# include "ms_other_utils.h"
# include "ms_double_linked_list.h"

void	ast_free(t_node **root);
void	ast_del_content_token(void *token);
void	ast_create(t_node **root, t_double_list *token_list);
void	ast_add_token_operator(t_node **root, t_token *token);
void	ast_add_token_literal(t_node **root, t_double_list *literal_list);
#endif