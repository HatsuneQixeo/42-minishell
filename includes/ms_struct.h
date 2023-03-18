/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_struct.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 23:30:59 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/18 14:44:48 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_STRUCT_H
# define MS_STRUCT_H

/* ********** DATA STRUCTURE ********** */

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
typedef struct s_ast
{
	int				type;
	char			*data;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

typedef enum e_asttype
{
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
	token_list = Store tokens.
	cursor = Point to the current token.
 */
typedef struct s_scanner
{
	t_double_list	*token_list;
	t_double_list	*cursor;
}	t_scanner;

typedef struct s_parser
{
	t_scanner	*scanner;
	t_ast		*cmd_ast;
	t_ast		**and_or_ast;
}	t_parser;

/* ********** EXECUTOR ********* */

typedef struct s_cmd
{
	int		argc;
	char	**argv;
}	t_cmd;

/* ********** DEBUG ********** */

typedef struct s_key_value
{
	t_asttype	key;
	void		*value;
}	t_key_value;
#endif