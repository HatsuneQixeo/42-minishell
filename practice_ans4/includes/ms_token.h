/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_token.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:05:45 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/02/13 13:15:43 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_TOKEN_H
# define MS_TOKEN_H

# include <stdlib.h>
# include <stdbool.h>

# include "libft.h"
# include "ms_double_linked_list.h"
# include "ms_debug.h"

typedef enum  e_token_type
{
	TOKEN_PIPELINE = 1,
	TOKEN_SEP_AND,
	TOKEN_SEP_OR,
	TOKEN_SEP_SEMICOLON,
	TOKEN_REDIR_LEFT,
	TOKEN_REDIR_RIGHT,
	TOKEN_REDIR_LEFT_DOUBLE,
	TOKEN_REDIR_RIGHT_DOUBLE,
	TOKEN_QUOTE_SINGLE,
	TOKEN_QUOTE_DOUBLE,
	TOKEN_LITERAL,
	TOKEN_VARIABLE,
	TOKEN_ESCAPE,
	TOKEN_SPACE,
	TOKEN_OPTION,
}   t_token_type;

typedef struct  s_grammar
{
	char            value;
	t_token_type    type;
}               t_grammar;

typedef struct  s_token
{
	void    		*value;
	t_token_type	type;
}				t_token;

/* token_utils */
t_token_type	ms_token_type_set(char c);
t_double_list	*ms_tokenizer(char *input);
void			ms_token_free(void	*token);
t_token_type	token_type_get(t_token *token);
void			ms_token_list_free(t_double_list **token_list);
t_token			*ms_token_create(void *value, t_token_type type);

/* token_utils2 */
bool		ms_token_is_space(char c);
bool		ms_token_is_operator(t_token *token);
bool		ms_token_is_separator(t_token *token);
void		ms_token_list_concat_same_type(t_double_list **head);
t_token		*concat_2_tokens(t_token *token_1, t_token *token_2, t_token_type type);

void	ms_token_free2(void *token, void (*del)(void *));
#endif