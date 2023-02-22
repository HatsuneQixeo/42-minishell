/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_struct.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 23:30:59 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/02/22 23:56:10 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_STRUCT_H
# define MS_STRUCT_H

/* ********** TOKENIZER ********** */

typedef enum e_token_type
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
}	t_token_type;

typedef struct s_grammar
{
	char			value;
	t_token_type	type;
}	t_grammar;

typedef struct s_token
{
	void			*value;
	t_token_type	type;
}	t_token;

/* ********** DATA STRUCTURE ********** */

/* Binary Tree */
typedef struct s_node
{
	void			*content;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

/* Double Linked List */
typedef struct s_double_list
{
	void					*content;
	struct s_double_list	*prev;
	struct s_double_list	*next;
}	t_double_list;

/* Stack */
typedef struct s_stack
{
	int		top;
	char	*arr;
	int		max_size;
}	t_stack;
#endif