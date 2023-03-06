/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_struct.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 23:30:59 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/05 16:36:34 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_STRUCT_H
# define MS_STRUCT_H

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

/* Abstract Syntax Tree */
typedef struct	s_ast
{
	int				type;
	char			*data;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

typedef enum	e_asttype{
	AST_PIPE =		(1 << 0),
	AST_SEQ =		(1 << 1),
	AST_AND =		(1 << 2),
	AST_OR =		(1 << 3),
	AST_REDIR =		(1 << 4),
	AST_RD_INFILE =	(1 << 5),
	AST_RD_HDOC =	(1 << 6),
	AST_RD_TRUNC =	(1 << 7),
	AST_RD_APPEND =	(1 << 8),
	AST_CMD =		(1 << 9),
	AST_ARG =		(1 << 10),
	AST_DATA =		(1 << 11)
}	t_asttype;

/* ********** TOKENIZER ********** */

typedef enum e_token_type
{
	UNKNOWN,
	PIPELINE,
	OR,
	AMPERSAND,
	AND,
	LESS,
	GREAT,
	DLESS,
	DGREAT,
	SEMICOLON,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	LITERAL,
	VARIABLE,
	EXPAND,
	BACKSLASH,
	SPACES,
	OPTION,
	OPEN_PAREN,
	CLOSE_PAREN,
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

/* ********** PARSER ********** */

/*
	cursor = Point to the current list.
	token_list = Store tokens.
	save_point = Save current list here when need.
 */
typedef struct	s_scanner
{
	t_double_list	*cursor;
	t_double_list	*token_list;
	t_double_list	*save_point;
}	t_scanner;
#endif