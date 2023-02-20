/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_token.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:05:45 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/02/21 00:10:41 by ntan-wan         ###   ########.fr       */
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
	UNKNOWN,
	PIPELINE,
	OR,
	AMPERSAND,
	AND,
	REDIR_LEFT,
	REDIR_RIGHT,
	REDIR_LEFT_DOUBLE,
	REDIR_RIGHT_DOUBLE,
	SEMICOLON,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	LITERAL,
	VARIABLE,
	EXPAND,
	BACKSLASH,
	SPACES,
	OPTION,
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
t_token_type	token_type_identify(char c);
t_double_list	*ms_tokenizer(char *input);
void			token_free(void	*token);
t_token_type	token_type_get(t_token *token);
void			token_list_free(t_double_list **token_list);
void			token_type_set(t_token *token, t_token_type type);
t_token			*token_create(void *value, t_token_type type);

/* token_utils2 */
bool		ms_token_is_space(char c);
bool		token_is_operator(t_token *token);
bool		ms_token_is_separator(t_token *token);
t_token		*concat_2_tokens(t_token *token_1, t_token *token_2, t_token_type type);

void	token_free_del(void *token, void (*del)(void *));
void	*token_value_get(t_token *token);
void	rm_token_value(t_token *token);
void	list_token_type_set(t_double_list *list, t_token_type set_type);
#endif