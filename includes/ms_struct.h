/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_struct.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 23:30:59 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/02 17:49:43 by ntan-wan         ###   ########.fr       */
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
	ASSIGN,
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

typedef struct	s_scanner
{
	t_double_list	*token_list;
	t_double_list	*current_list;	
}	t_scanner;

typedef struct	s_cmd_word
{
	char	*word;
}	t_cmd_word;

typedef struct	s_cmd_name
{
	char	*word;
}	t_cmd_name;

/* 
	@brief "<", "<&", ">", ">&", ">>"
 */
// typedef enum	e_io_type
// {
// 	LESS,
// 	LESSAND,
// 	GREAT,
// 	GREATAND,
// 	DGREAT,
// }	t_io_type;

typedef struct	s_file_name
{
	char	*word;
}	t_file_name;

typedef struct	s_here_end
{
	char	*word;
}	t_here_end;

typedef struct	s_io_file
{
	t_file_name		*file_name;
	t_token_type	type;
}	t_io_file;

typedef struct	s_io_here
{
	//DLESS
	t_here_end	*here_end;
}	t_io_here;

typedef struct	s_io_redirect
{
	int			io_num;
	int			io_default;
	t_io_file	*io_file;
	t_io_here	*io_here;
}	t_io_redirect;

typedef struct	s_cmd_prefix
{
	t_double_list	*io_redirect;
	t_double_list	*assignment_word;
}	t_cmd_prefix;

typedef struct	s_cmd_suffix
{
	t_double_list	*io_redirect;
	t_double_list	*words;
}	t_cmd_suffix;

typedef	struct	s_simple_cmd
{
	t_cmd_prefix	*prefix;
	t_cmd_suffix	*suffix;
	t_cmd_name		*cmd_name;
	t_cmd_word		*cmd_word;	
}	t_simple_cmd;

// typedef struct	s_complete_cmd
// {
// 	t_double_list	*list;
// 	t_sep_operator	*sep_op;
// }	t_complete_cmd;
#endif