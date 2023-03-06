/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 10:31:20 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/07 01:04:15 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_scanner	*scanner_init(t_double_list *token_list)
{
	t_scanner	*scanner;

	scanner = malloc(sizeof(t_scanner));
	if (scanner)
	{
		scanner->token_list = token_list;
		scanner->cursor = token_list;
		scanner->save_point = token_list;
	}
	return (scanner);
}

/* 
	@brief Get current token from scanner.
	@return Return pointer to t_token.
 */
t_token	*s_get_token(t_scanner *scanner)
{
	if (scanner->cursor)
		return (scanner->cursor->content);
	else
		return (NULL);
}

/* 
	@brief Save current list as save point.
 */
void	scanner_save(t_scanner *scanner)
{
	scanner->save_point = scanner->cursor;
}

/* 
	@brief Reset cursor to previous save point.
 */
void	scanner_reset(t_scanner *scanner)
{
	scanner->cursor = scanner->save_point;
}

/* 
	@brief Check whether cursor reached the end of token list.
 */
bool	scanner_has_tokens(t_scanner *scanner)
{
	return (scanner->cursor);
}
/* 
	@brief Read the next list and advance the cursor.
	@return Return next list.
*/
t_double_list	*s_next(t_scanner *scanner)
{
	if (scanner->cursor)
		scanner->cursor = scanner->cursor->next;
	return (scanner->cursor);
}

void	scanner_free(t_scanner **scanner)
{
	if (!*scanner)
		return ;
	token_list_free(&(*scanner)->token_list);
	free(*scanner);
	*scanner = NULL;
}

void	ast_settype(t_ast *node, t_asttype type)
{
	if (!node)
		return ;
	node->type = type;
}

void	ast_setdata(t_ast *node, char *data)
{
	if (!node || !data)
		return ;
	node->data = data;
	node->type |= AST_DATA;
}

void	ast_attach(t_ast *root, t_ast *left, t_ast *right)
{
	if (!root)
		return ;
	root->left = left;
	root->right = right;
}

void	ast_insert_right(t_ast *root, t_ast *node)
{
	t_ast	*tmp;

	if (!root || !node)
		return ;
	tmp = root->right;
	root->right = node;	
	node->right = tmp;
	node->left = NULL;
}

int	ast_gettype(t_ast *node)
{
	return (node->type & (~AST_DATA));
}

void	ast_insert_left(t_ast *root, t_ast *node)
{
	t_ast	*tmp;

	if (!root || !node)
		return ;
	tmp = root->left;
	root->left = node;	
	node->left = tmp;
	node->right = NULL;
}

void	ast_delete(t_ast **node)
{
	if (!*node)
		return ;
	if ((*node)->type & AST_DATA)
		free((*node)->data);
	ast_delete(&(*node)->left);
	ast_delete(&(*node)->right);
	free(*node);
	*node = NULL;
}

/* ********** PARSER ********** */

bool	s_have_tokens_left(t_scanner *s)
{
	return (s->cursor);
}

/* '<<' [file_name] */
t_ast	*redir_test_1_heredoc(t_scanner *s)
{
	char	*file;
	t_ast	*node;

	node = NULL;
	if (s_have_tokens_left(s) && s_get_token(s)->type == DLESS)
	{
		s_next(s);
		if (s_have_tokens_left(s) && s_get_token(s)->type == LITERAL)
		{
			file = ft_strdup(s_get_token(s)->value);
			node = ft_calloc(1, sizeof(t_ast));
			ast_settype(node, AST_RD_HDOC);
			ast_setdata(node, file);
			ast_attach(node, NULL, NULL);
			s_next(s);
			return (node);
		}
		return (NULL);
	}
	return (NULL);
}

/*  '<' [file_name] */
t_ast	*redir_test_2_infile(t_scanner *s)
{
	char	*file;
	t_ast	*node;

	node = NULL;
	if (s_have_tokens_left(s) && s_get_token(s)->type == LESS)
	{
		s_next(s);
		if (s_have_tokens_left(s) && s_get_token(s)->type == LITERAL)
		{
			file = ft_strdup(s_get_token(s)->value);
			node = ft_calloc(1, sizeof(t_ast));
			ast_settype(node, AST_RD_INFILE);
			ast_setdata(node, file);
			ast_attach(node, NULL, NULL);
			s_next(s);
			return (node);
		}
		return (NULL);
	}
	return (NULL);
}

t_ast	*parse_redir_in(t_scanner *s)
{
	t_ast	*new_node;
	t_double_list	*save;

	// scanner_save(s);
	save = s->cursor;
	new_node = redir_test_1_heredoc(s);
	if (new_node)
		return (new_node);
	// scanner_reset(s);
	s->cursor = save;
	new_node = redir_test_2_infile(s);
	if (new_node)
		return (new_node);
	return (NULL);
}

/* '>> [file_name] */
t_ast	*redir_test_1_append(t_scanner *s)
{
	char	*file;
	t_ast	*node;

	node = NULL;
	if (s_have_tokens_left(s) && s_get_token(s)->type == DGREAT)
	{
		s_next(s);
		if (s_have_tokens_left(s) && s_get_token(s)->type == LITERAL)
		{
			file = ft_strdup(s_get_token(s)->value);
			node = ft_calloc(1, sizeof(t_ast));
			ast_settype(node, AST_RD_APPEND);
			ast_setdata(node, file);
			ast_attach(node, NULL, NULL);
			s_next(s);
			return (node);
		}
		return (NULL);
	}
	return (NULL);
}
/* '>' [file_name] */
t_ast	*redir_test_2_outfile(t_scanner *s)
{
	char	*file;
	t_ast	*node;

	node = NULL;
	if (s_have_tokens_left(s) && s_get_token(s)->type == GREAT)
	{
		s_next(s);
		if (s_have_tokens_left(s) && s_get_token(s)->type == LITERAL)
		{
			file = ft_strdup(s_get_token(s)->value);
			node = ft_calloc(1, sizeof(t_ast));
			ast_settype(node, AST_RD_TRUNC);
			ast_setdata(node, file);
			ast_attach(node, NULL, NULL);
			s_next(s);
			return (node);
		}
		return (NULL);
	}
	return (NULL);
}

t_ast	*parse_redir_out(t_scanner *s)
{
	t_ast	*new_node;
	t_double_list	*save;

	// scanner_save(s);
	save = s->cursor;
	new_node = redir_test_1_append(s);
	if (new_node)
		return (new_node);
	// scanner_reset(s);
	s->cursor = save;
	new_node = redir_test_2_outfile(s);
	if (new_node)
		return (new_node);
	return (NULL);
}

t_ast	*redir_test_1_in(t_scanner *s)
{
	t_ast	*node;

	node = parse_redir_in(s);
	if (node)
	{
		ast_attach(node, NULL, NULL);
		return (node);
	}
	return (NULL);
}

t_ast	*redir_test_2_out(t_scanner *s)
{
	t_ast	*node;

	node = parse_redir_out(s);
	if (node)
	{
		ast_attach(node, NULL, NULL);
		return (node);
	}
	return (NULL);
}

t_ast	*parse_redir(t_scanner *s)
{
	t_ast	*new_node;
	t_double_list	*save;

	// scanner_save(s);
	save = s->cursor;
	new_node = redir_test_1_in(s);
	if (new_node)
		return (new_node);
	// scanner_reset(s);
	s->cursor = save;
	new_node = redir_test_2_out(s);
	if (new_node)
		return (new_node);
	return (NULL);
}

t_ast	*cmd_ast(t_ast *node)
{
	static t_ast	*cmd_ast;

	if (!cmd_ast)
		cmd_ast = ft_calloc(1, sizeof(t_ast));
	if (node)
		cmd_ast = node;
	return (cmd_ast);
}

/* [cmd_name] [token_list] */
// uses global cmd_ast
t_ast	*tokenlist_test_1_cmd_name(t_scanner *s)
{
	char	*name;
	t_token	*token;
	
	token = s_get_token(s);
	if (cmd_ast(NULL)->data == NULL)
	{
		if (s_have_tokens_left(s) && s_get_token(s)->type == LITERAL)
		{
			name = ft_strdup(s_get_token(s)->value);
			ast_setdata(cmd_ast(NULL), name);
			s_next(s);
			parse_tokenlist(s);
			return (cmd_ast(NULL));
		}
	}
	return (NULL);
}

/* [redir] [token_list] */
// uses global ast
t_ast	*tokenlist_test_2_redir(t_scanner *s)
{
	t_ast	*node;
	
	node = parse_redir(s);
	if (node)
	{
		parse_tokenlist(s);
		ast_insert_left(cmd_ast(NULL), node);
		return (node);
	}
	return (NULL);
}

/* [token] [token_list] = [token_args]*/
t_ast	*tokenlist_test_3_args(t_scanner *s)
{
	char	*arg;
	t_ast	*node;

	if (s_have_tokens_left(s) && s_get_token(s)->type == LITERAL)
	{
		arg = ft_strdup(s_get_token(s)->value);
		node = ft_calloc(1, sizeof(t_ast));
		ast_settype(node, AST_ARG);
		ast_setdata(node, arg);
		s_next(s);
		parse_tokenlist(s);
		ast_insert_right(cmd_ast(NULL), node);
		return (node);
	}
	return (NULL);
}

t_ast	*test(t_ast *(*func)(t_scanner *), t_scanner *s)
{
	// scanner_save(s);
	// *node = func(s);
	// if (!*node)
	// 	scanner_reset(s);
	t_ast	*new_node;

	new_node = NULL;
	scanner_save(s);
	new_node = func(s);
	if (!new_node)
		scanner_reset(s);
	return (new_node);
}

t_ast	*parse_tokenlist(t_scanner *s)
{
	t_ast		*new_node;
	t_double_list	*save;

	// new_node = test(tokenlist_test_1_cmd_name, s);
	// new_node = test(tokenlist_test_2_redir, s);
	// new_node = test(tokenlist_test_3_args, s);
	// scanner_save(s);
	save = s->cursor;
	new_node = tokenlist_test_1_cmd_name(s);
	if (new_node)
		return (new_node);
	// scanner_reset(s);
	s->cursor = save;
	new_node = tokenlist_test_2_redir(s);
	if (new_node)
		return (new_node);
	// scanner_reset(s);
	s->cursor = save;
	new_node = tokenlist_test_3_args(s);
		return (new_node);
	return (NULL);
}


/* [name] [token_list]*/
t_ast	*cmd_test_1(t_scanner *s)
{
	t_ast	*node;

	node = ft_calloc(1, sizeof(t_ast));
	node->data = NULL;
	ast_attach(node, NULL, NULL);
	ast_settype(node, AST_CMD);
	cmd_ast(node);
	parse_tokenlist(s);
	if (node != NULL && node->data == NULL && node->left == NULL && node->right == NULL)
	{
		free(node);
		return (NULL);
	}
	return (node);
}

t_ast	*parse_cmd(t_scanner *s)
{
	return (cmd_test_1(s));
}

bool	s_token_type_matches(t_token_type match_type, t_scanner *s)
{
	//
	// printf("%s\n", (char *)token_value_get(s->cursor->content));
	return (s_have_tokens_left(s) && s_get_token(s)->type == match_type);
}

t_ast	*parse_job(t_scanner *s);

t_ast	*job_test_4(t_scanner *s);

/* '(' [command] ')' '|' [job] */
t_ast	*job_test_1(t_scanner *s)
{
	t_ast	*cmd_node;
	t_ast	*job_node;
	t_ast	*node;

	if (s_token_type_matches(OPEN_PAREN, s))
	{
		s_next(s);
		cmd_node = parse_cmd(s);
		if (cmd_node)
		{
			// if (s_token_type_matches(CLOSE_PAREN, s) || s_token_type_matches(PIPELINE, s))
			if (s_token_type_matches(CLOSE_PAREN, s))
			{
				s_next(s);
				if (s_token_type_matches(PIPELINE, s))
				{
					s_next(s);
					job_node = parse_job(s);
					if (job_node)
					{
						node = ft_calloc(1, sizeof(t_ast));
						ast_settype(node, AST_PIPE);
						ast_attach(node, cmd_node, job_node);
						return (node);
					}
				}
			}
			ast_delete(&cmd_node);
		}
	}
	return (NULL);
}

/* [command] '|' [job] */
t_ast	*job_test_2(t_scanner *s)
{
	t_ast	*cmd_node;
	t_ast	*job_node;
	t_ast	*node;

	cmd_node = parse_cmd(s);
	if (cmd_node)
	{
		if (s_token_type_matches(PIPELINE, s))
		{
			//
			s_next(s);
			job_node = parse_job(s);
			// printf("%s\n", (char *)token_value_get(s->cursor->content));
			// job_node = job_test_4(s);
			if (job_node)
			{
				node = ft_calloc(1, sizeof(t_ast));
				ast_settype(node, AST_PIPE);
				ast_attach(node, cmd_node, job_node);
				return (node);
			}
		}
		ast_delete(&cmd_node);
	}
	return (NULL);
}

/* '(' [command] ')' */
t_ast	*job_test_3(t_scanner *s)
{
	t_ast	*cmd_node;

	if (s_token_type_matches(OPEN_PAREN, s))
	{
		s_next(s);
		cmd_node = parse_cmd(s);
		if (cmd_node)
		{
			if (s_token_type_matches(CLOSE_PAREN, s))
			{
				s_next(s);
				return (cmd_node);
			}
			ast_delete(&cmd_node);
		}
	}
	return (NULL);
}

/* [command] */
t_ast	*job_test_4(t_scanner *s)
{
	return (parse_cmd(s));
}

t_ast	*parse_job(t_scanner *s)
{
	t_ast	*node;
	t_double_list	*save;

	// scanner_save(s);
	save = s->cursor;
	node = job_test_1(s);
	if (node)
		return (node);
	// scanner_reset(s);
	s->cursor = save;
	node = job_test_2(s);
	if (node)
		return (node);
	// scanner_reset(s);
	s->cursor = save;
	node = job_test_3(s);
	if (node)
		return (node);
	// scanner_reset(s);
	s->cursor = save;
	node = job_test_4(s);
	if (node)
		return (node);
	return (NULL);
}

t_ast	*parse_cmd_line(t_scanner *s);
t_ast	*parse_and_or(t_scanner *s);

t_ast	**and_or_ast(t_ast *node)
{
	static t_ast	**and_or_ast;

	if (!and_or_ast)
		and_or_ast = ft_calloc(1, sizeof(t_ast *));
	if (node)
		*and_or_ast = node;
	return (and_or_ast);
}

void	ast_insert_and_or(t_ast **root, t_ast *new_root, bool last)
{
	if (root == NULL || new_root == NULL)
		return ;
	if (*root == NULL)
		*root = new_root;
	else
	{
		if (last == false)
		{
			(*root)->right = new_root->left;
			new_root->left = (*root);
			*root = new_root;
		}
		else
		{
			(*root)->right = new_root;
		}
	}
}


/* [job] '&&' [and_or] */
t_ast	*and_or_1(t_scanner *s)
{
	t_ast	*job_node;
	t_ast	*node;

	job_node = parse_job(s);
	if (job_node)
	{
		if (s_token_type_matches(AND, s))
		{
			s_next(s);
			node = ft_calloc(1, sizeof(t_ast));
			ast_settype(node, AST_AND);
			ast_attach(node, job_node, NULL);
			ast_insert_and_or(and_or_ast(NULL), node, false);
			if (!parse_and_or(s))
				return (NULL);
			return (node);
		}
		ast_delete(&job_node);
	}
	return (NULL);
}

t_ast	*and_or_2(t_scanner *s)
{
	t_ast	*job_node;
	t_ast	*node;

	job_node = parse_job(s);
	if (job_node)
	{
		if (s_token_type_matches(OR, s))
		{
			s_next(s);
			node = ft_calloc(1, sizeof(t_ast));
			ast_settype(node, AST_OR);
			ast_attach(node, job_node, NULL);
			ast_insert_and_or(and_or_ast(NULL), node, false);
			if (!parse_and_or(s))
				return (NULL);
			return (node);
		}
	}
}

/* [job] */
t_ast	*and_or_3(t_scanner *s)
{
	t_ast	*node;
	
	node = parse_job(s);
	if (node)
		ast_insert_and_or(and_or_ast(NULL), node, true);
	return (node);
}

t_ast	*new_and_or_node(int type, t_ast *cmd_line_node)
{
	t_ast	*node;

	node = ft_calloc(1, sizeof(t_ast));
	ast_settype(node, type);
	ast_attach(node, cmd_line_node, NULL);
	ast_insert_and_or(and_or_ast(NULL), node, false);
	return (NULL);
}

/* '(' [command line] ')' && [and_or] */
t_ast	*and_or_4(t_scanner *s)
{
	t_ast	*cmd_line_node;
	t_ast	*node;
	t_ast	*save;

	save = *and_or_ast(NULL);
	if (s_token_type_matches(OPEN_PAREN, s))
	{
		s_next(s);
		cmd_line_node = parse_cmd_line(s);
		if (cmd_line_node)
		{
			if (s_token_type_matches(CLOSE_PAREN, s))
			{
				s_next(s);
				if (s_token_type_matches(AND, s))
				{
					s_next(s);
					node = new_and_or_node(AST_AND, cmd_line_node);
					if (!parse_and_or(s))
						return (NULL);
					return (node);
				}
			}
			ast_delete(&cmd_line_node);
		}
		and_or_ast(save);
	}
	return (NULL);
}

/* '(' [command_line] ')' || [and_or] */
t_ast	*and_or_5(t_scanner *s)
{
	t_ast	*cmd_line_node;
	t_ast	*parent_node;
	t_ast	*save;

	save = *and_or_ast(NULL);
	if  (s_token_type_matches(OPEN_PAREN, s))
	{
		s_next(s);
		cmd_line_node = parse_cmd_line(s);
		if (cmd_line_node)	
		{
			and_or_ast(save);
			if (s_token_type_matches(CLOSE_PAREN, s))
			{
				s_next(s);
				if (s_token_type_matches(OR, s))
				{
					s_next(s);
					parent_node = new_and_or_node(AST_OR, cmd_line_node);
					if (!parse_and_or(s))
						return (NULL);
					return (parent_node);
				}
			}
			ast_delete(&cmd_line_node);
		}
		and_or_ast(save);
	}
	return (NULL);
}

/* '(' [command line] ')' */

t_ast	*and_or_6(t_scanner *s)
{
	t_ast	*cmd_line_node;
	t_ast	*save;

	save = *and_or_ast(NULL);
	if (s_token_type_matches(OPEN_PAREN, s))
	{
		s_next(s);
		cmd_line_node = parse_cmd_line(s);
		if (cmd_line_node)
		{
			and_or_ast(save);
			if (s_token_type_matches(OPEN_PAREN, s))
			{
				ast_insert_and_or(and_or_ast(NULL), cmd_line_node, true);
				return (cmd_line_node);
			}
			ast_delete(&cmd_line_node);
		}
		and_or_ast(save);
	}
	return (NULL);
}

t_ast	*parse_and_or(t_scanner *s)
{
	t_double_list	*save;
	t_ast			*new_node;

	save = s->cursor;
	new_node = and_or_1(s);
	if (new_node != NULL)
		return (new_node);
	s->cursor = save;
	new_node = and_or_2(s);
	if (new_node != NULL)
		return (new_node);
	s->cursor = save;
	new_node = and_or_3(s);
	if (new_node != NULL)
		return (new_node);
	s->cursor = save;
	new_node = and_or_4(s);
	if (new_node != NULL)
		return (new_node);
	s->cursor = save;
	new_node = and_or_5(s);
	if (new_node != NULL)
		return (new_node);
	s->cursor = save;
	new_node = and_or_6(s);
	if (new_node != NULL)
		return (new_node);
	return (NULL);
}

/* [and_or] ';' [command_line] */
t_ast	*cmd_line_1(t_scanner* s)
{
	t_ast	*and_or_node;
	t_ast	*cmd_line_node;
	t_ast	*parent_node;

	*and_or_ast(NULL) = NULL;
	parse_and_or(s);
	and_or_node = *and_or_ast(NULL);
	if (and_or_node)
	{
		if (s_token_type_matches(SEMICOLON, s))
		{
			s_next(s);
			cmd_line_node = parse_cmd_line(s);
			if (cmd_line_node)
			{
				parent_node = ft_calloc(1, sizeof(t_ast));
				ast_settype(parent_node, AST_SEQ);
				ast_attach(parent_node, and_or_node, cmd_line_node);
				return (parent_node);
			}
		}
		ast_delete(&and_or_node);
	}
	return (NULL);
}

/* [and_or] ';' */
t_ast	*cmd_line_2(t_scanner *s)
{
	t_ast	*and_or_node;
	t_ast	*parent_node;

	*and_or_ast(NULL) = NULL;
	parse_and_or(s);
	and_or_node = *and_or_ast(NULL);
	if (and_or_node)
	{
		if (s_token_type_matches(SEMICOLON, s))
		{
			s_next(s);
			parent_node = ft_calloc(1, sizeof(t_ast));
			ast_settype(parent_node, AST_SEQ);
			ast_attach(parent_node, and_or_node, NULL);
			return (parent_node);
		}
		ast_delete(&and_or_node);
	}
	return (NULL);
}
/* [and_or] */
t_ast	*cmd_line_3(t_scanner *s)
{
	t_ast	*and_or_node;

	// and_or_node = NULL;
	*and_or_ast(NULL) = NULL;
	parse_and_or(s);
	and_or_node = *and_or_ast(NULL);
	if (and_or_node == NULL)
		return (NULL);
	return (and_or_node);
}

t_ast	*parse_cmd_line(t_scanner *s)
{
	t_double_list	*save;
	t_ast	*new_node;

	save = s->cursor;
	s->cursor = save;
	new_node = cmd_line_1(s);
	if (new_node != NULL)
		return (new_node);
	s->cursor = save;
	new_node = cmd_line_2(s);
	if (new_node != NULL)
		return (new_node);
	s->cursor = save;
	new_node = cmd_line_3(s);
	if (new_node != NULL)
		return (new_node);
	return (NULL);
}