/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:54:58 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/02/20 22:42:06 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include <stdbool.h>
# include "libft.h"

typedef enum
{
	TOKEN_UNKNOWN,
	TOKEN_WORD,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_HEREDOC,
	TOKEN_APPEND,
	TOKEN_PIPE,
	TOKEN_OR,
	TOKEN_AND,
	OPTION,
} t_token_type;



typedef struct	s_token_type_key_value
{
	char			*key;
	t_token_type	value;
}	t_token_type_key_value;

typedef struct	s_token
{
	char			*value;
	t_token_type	type;
}	t_token;

t_list			*ms_tokenize(char *input);
t_token			*token_init(char *token_value);
t_token_type	token_type_get(char *token_value);
char			*token_value_get(char *token_start, char *token_end);
void			token_free(void *token);
void			token_list_free(t_list	**token_list);


char	*ms_strtok(char *str, char *delimiter);

/* version 3 */

typedef enum e_token_type3
{
	LITERAL,
	OPTION3,
	PIPELINE,
	AMPERSAND,
	OR,
	TOKEN_SEP_SEIMICOLON,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_HEREDOC,
	TOKEN_REDIR_APPEND,
}	t_token_type3;

typedef struct	s_token_type_grammar
{
	char			*value;
	t_token_type3	type;
}				t_token_type_grammar;
#endif