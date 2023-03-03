/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 22:37:13 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/03 14:34:31 by ntan-wan         ###   ########.fr       */
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
		scanner->current_list = token_list;
	}
	return (scanner);
}

/* 
	@brief Peek the next list but do not advance the cursor.
	@return Return next list.
 */
t_double_list	*scanner_peek(t_scanner *self)
{
	t_double_list	*next_list;

	next_list = NULL;
	if (self->token_list)
		next_list = self->current_list->next;
	return (next_list);
}

/* 
	@brief Read the previous list and move one step back the cursor.
	@return prev list.
 */
t_double_list	*scanner_prev(t_scanner *self)
{
	if (self->current_list)
		self->current_list = self->current_list->prev;
	return (self->current_list);
}

/* 
	@brief Read the next list and advance the cursor.
	@return Return next list.
*/
t_double_list	*scanner_next(t_scanner *self)
{
	t_token	*token;

	token = self->current_list->content;
	if (self->current_list)
		self->current_list = self->current_list->next;
	return (self->current_list);
}

void	scanner_free(t_scanner **self)
{
	token_list_free(&(*self)->token_list);
	free(*self);
	*self = NULL;
}

void	cmd_word_free(t_cmd_word **cmd_word)
{
	if (!*cmd_word)
		return ;
	if ((*cmd_word)->word)
	{
		free((*cmd_word)->word);
		(*cmd_word)->word = NULL;
	}
	free(*cmd_word);
	*cmd_word = NULL;
}

/* 
	@note Advance cursor upon SUCCESS
 */
int	parse_cmd_word(t_scanner *scanner, t_cmd_word **cmd_word)
{
	t_double_list	*current_list;

	current_list = scanner->current_list;
	if (!current_list)
		return (EMPTY);
	else if (token_type_get(current_list->content) == LITERAL)
	{
		*cmd_word =ft_calloc(1, sizeof(t_cmd_word));
		(*cmd_word)->word = ft_strdup(token_value_get(current_list->content));
		scanner_next(scanner);
		//
		printf("cmd_word -> %s\n", (*cmd_word)->word);
		return (SUCCESS);
	}
	else
		*cmd_word = NULL;
	// return (ERROR);
	return (EMPTY);
}

void	cmd_name_free(t_cmd_name **cmd_name)
{
	if (!*cmd_name)
		return ;
	if ((*cmd_name)->word)
		free((*cmd_name)->word);
	free(*cmd_name);
	*cmd_name = NULL;
}

/* 
	@note Advance cursor upon SUCCESS
 */
int	parse_cmd_name(t_scanner *scanner, t_cmd_name **cmd_name)
{
	t_double_list	*current_list;

	current_list = scanner->current_list;
	if (!current_list)
		return (ERROR);
	else if (token_type_get(current_list->content) == LITERAL)
	{
		*cmd_name = ft_calloc(1, sizeof(t_cmd_name));
		(*cmd_name)->word = ft_strdup(token_value_get(current_list->content));
		//
		printf("cmd_name -> %s\n", (*cmd_name)->word);
		scanner_next(scanner);
		return (SUCCESS);
	}
	else
		*cmd_name = NULL;
	return (ERROR);
}

void	file_name_free(t_file_name **file_name)
{
	if (!*file_name)
		return ;
	if ((*file_name)->word)
	{
		free((*file_name)->word);
		(*file_name)->word = NULL;
	}
	free(*file_name);
	*file_name = NULL;
}

/* 
	@note Advance cursor upon SUCCESS
 */
int	parse_file_name(t_scanner *scanner, t_file_name **file_name)
{
	t_double_list	*current_list;

	current_list = scanner->current_list;
	if (!current_list)
		return (ERROR);
	else if (token_type_get(current_list->content) == LITERAL)
	{
		// expansion()...
		*file_name = ft_calloc(1, sizeof(t_cmd_name));
		(*file_name)->word = ft_strdup(token_value_get(current_list->content));
		//
		printf("file_name -> %s\n", (*file_name)->word);
		scanner_next(scanner);
		return (SUCCESS);
	}
	else
		*file_name = NULL;
	return (ERROR);
}

void	here_end_free(t_here_end **here_end)
{
	if (!*here_end)
		return ;
	if ((*here_end)->word)
	{
		free((*here_end)->word);
		(*here_end)->word = NULL;
	}
	free(*here_end);
	*here_end = NULL;
}

/* 
	@note Advance cursor upon SUCCESS
 */
int		parse_here_end(t_scanner *scanner, t_here_end **here_end)
{
	t_double_list	*current_list;

	current_list = scanner->current_list;
	if (!current_list)
		return (ERROR);
	else if (token_type_get(current_list->content) == LITERAL)
	{
		*here_end = ft_calloc(1, sizeof(t_here_end));
		(*here_end)->word = ft_strdup(token_value_get(current_list->content));
		// 
		printf("here_end -> %s\n", (*here_end)->word);
		scanner_next(scanner);
		return (SUCCESS);
	}
	else
		*here_end = NULL;
	return (ERROR);
}

void	io_here_free(t_io_here **io_here)
{
	if (!*io_here)
		return ;
	here_end_free(&(*io_here)->here_end);
	free(*io_here);
	*io_here = NULL;
}

/* 
	@note Advance cursor upon SUCCESS, revert cursor if ERROR
	free error
 */
//ERR_SYNTAX?
int	parse_io_here(t_scanner *scanner, t_io_here **io_here)
{
	t_double_list	*current_list;

	current_list = scanner->current_list;
	if (!current_list)
		return (ERROR);
	*io_here = ft_calloc(1, sizeof(t_io_here));
	if (token_type_get(current_list->content) == DLESS)
	{
		scanner_next(scanner);
		if (parse_here_end(scanner, &(*io_here)->here_end) == SUCCESS)
			return (SUCCESS);
		else
		{
			scanner_prev(scanner);
			io_here_free(io_here);
			return (ERROR);
		}
	}
	io_here_free(io_here);
	return (EMPTY);
}

void	io_file_free(t_io_file **io_file)
{
	if (!*io_file)
		return ;
	file_name_free(&(*io_file)->file_name);
	free(*io_file);
	*io_file = NULL;
}

/* 
	@note Advance cursor upon SUCCESS, revert cursor if ERROR
 */
// ERR_SYNTAX?
int	parse_io_file(t_scanner *scanner, t_io_file **io_file)
{
	t_double_list	*current_list;

	current_list = scanner->current_list;
	if (!current_list)
		return (ERROR);
	*io_file = ft_calloc(1, sizeof(t_io_file));
	if (token_is_redir(current_list->content))
	{
		(*io_file)->type = token_type_get(current_list->content);
		scanner_next(scanner);
		if (parse_file_name(scanner, &(*io_file)->file_name) == SUCCESS)
			return (SUCCESS);
		else
		{
			scanner_prev(scanner);
			io_file_free(io_file);
			return (ERROR);
		}
	}
	else
		io_file_free(io_file);
	return (EMPTY);
}

void	io_redir_free(t_io_redirect **io_redir)
{
	if (!*io_redir)
		return ;
	io_file_free(&(*io_redir)->io_file);
	io_here_free(&(*io_redir)->io_here);
	free(*io_redir);
	*io_redir = NULL;
}

/* 
	
 */
int	parse_io_redirect(t_scanner *scanner, t_io_redirect **io_redir)
{
	int	io_file_status;
	int	io_here_status;
	
	io_file_status = SUCCESS;
	io_here_status = SUCCESS;
	*io_redir = ft_calloc(1, sizeof(t_io_redirect));
	// parse_io_num()...
	(*io_redir)->io_default = 1;
	io_file_status = parse_io_file(scanner, &(*io_redir)->io_file);
	if (io_file_status == EMPTY)
		io_here_status = parse_io_here(scanner, &(*io_redir)->io_here);
	if (io_file_status == ERROR || io_here_status == ERROR)
	{
		io_redir_free(io_redir);
		return (ERROR);
	}
	else if (io_file_status == EMPTY && io_here_status == EMPTY)
	{
		io_redir_free(io_redir);
		return (EMPTY);
	}
	else
		return (SUCCESS);
}

void	cmd_prefix_io_redir_free(t_double_list **cmd_prefix_io_redir)
{
	t_double_list	*tmp;
	t_double_list	*next;

	tmp = *cmd_prefix_io_redir;
	while (tmp)
	{
		next = tmp->next;
		io_redir_free((t_io_redirect **)&tmp->content);
		free(tmp);
		tmp = next;
	}
	*cmd_prefix_io_redir = NULL;
}

int	parse_cmd_prefix_io_redir(t_scanner *scanner, t_cmd_prefix *cmd_prefix)
{
	t_io_redirect	*io_redir;
	int				io_redir_status;

	io_redir = NULL;
	io_redir_status = parse_io_redirect(scanner, &io_redir);
	//
	if (io_redir_status == ERROR || io_redir_status == EMPTY)
		return (io_redir_status);
	else
		double_lstadd_back(&cmd_prefix->io_redirect, double_lstnew(io_redir));
	return (SUCCESS);
}

// haven't test
void	cmd_prefix_assignment_free(t_double_list **cmd_prefix_assign)
{
	double_lstclear(cmd_prefix_assign, free);
}

// haven't test
int	parse_cmd_prefix_assignment(t_scanner *scanner, t_cmd_prefix *cmd_prefix)
{
	char			*value;
	t_double_list	*current_list;

	current_list = scanner->current_list;
	if (!current_list)
		return (ERROR);
	else if (token_type_get(current_list->content) == ASSIGN)
	{
		value = ft_strdup(token_value_get(current_list->content));
		double_lstadd_back(&cmd_prefix->assignment_word, double_lstnew(value));
		return (SUCCESS);
	}
	return (ERROR);
}

int	cmd_prefix_add(t_scanner *scanner, t_cmd_prefix *cmd_prefix)
{
	int	status;	
	
	status = parse_cmd_prefix_io_redir(scanner, cmd_prefix);
	//
	if (status == EMPTY)
		status = parse_cmd_prefix_assignment(scanner, cmd_prefix);
	return (status);
}

void	cmd_prefix_free(t_cmd_prefix **cmd_prefix)
{
	if (!*cmd_prefix)
		return ;
	cmd_prefix_io_redir_free(&(*cmd_prefix)->io_redirect);
	cmd_prefix_assignment_free(&(*cmd_prefix)->assignment_word);
	free(*cmd_prefix);
	*cmd_prefix = NULL;
}

// scanner_list->current_list == NULL? haven't handle when iterate to the end
int	parse_cmd_prefix(t_scanner *scanner, t_cmd_prefix **cmd_prefix)
{
	int	status;

	*cmd_prefix = ft_calloc(1, sizeof(t_cmd_prefix));
	status = cmd_prefix_add(scanner, *cmd_prefix);
	if (status == SUCCESS)
	{
		while (status == SUCCESS)
			status = cmd_prefix_add(scanner, *cmd_prefix);
		return (SUCCESS);
	}
	else
		cmd_prefix_free(cmd_prefix);
	return (EMPTY);
	// return (ERROR);
	// return (SUCCESS);
}

int	parse_simple_cmd_prefix(t_scanner *scanner, t_simple_cmd *simple_cmd)
{
	if (parse_cmd_prefix(scanner, &simple_cmd->prefix) == SUCCESS)
	{
		if (parse_cmd_word(scanner, &simple_cmd->cmd_word) == ERROR)
		{
			cmd_prefix_free(&simple_cmd->prefix);
			return (ERROR);
		}
	}
	else if (parse_cmd_name(scanner, &simple_cmd->cmd_name) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	parse_cmd_suffix_io_redir(t_scanner *scanner, t_cmd_suffix *cmd_suffix)
{
	t_io_redirect	*io_redir;
	int				io_redir_status;

	io_redir = NULL;
	io_redir_status = parse_io_redirect(scanner, &io_redir);
	if (io_redir_status == ERROR || io_redir_status == EMPTY)
		return (io_redir_status);
	else
		double_lstadd_back(&cmd_suffix->io_redirect, double_lstnew(io_redir));
	return (SUCCESS);
}

int parse_cmd_suffix_words(t_scanner *scanner, t_cmd_suffix *cmd_suffix)
{
	char			*value;
	t_double_list	*current_list;

	current_list = scanner->current_list;
	if (!current_list)
		return (ERROR);
	else if (token_type_get(current_list->content) == LITERAL)
	{
		value = ft_strdup(token_value_get(current_list->content));
		double_lstadd_back(&cmd_suffix->words, double_lstnew(value));
		//
		printf("cmd_suffix_words -> %s\n", value);
		scanner_next(scanner);
		return (SUCCESS);
	}
	// return (ERROR);
	return (EMPTY);
}

int	cmd_suffix_add(t_scanner *scanner, t_cmd_suffix *cmd_suffix)
{
	int	status;	
	
	status = parse_cmd_suffix_io_redir(scanner, cmd_suffix);
	if (status == EMPTY)
		status = parse_cmd_suffix_words(scanner, cmd_suffix);
	return (status);
}

void	cmd_suffix_free(t_cmd_suffix **cmd_suffix)
{
	if (!*cmd_suffix)
		return ;
	cmd_prefix_io_redir_free(&(*cmd_suffix)->io_redirect);
	cmd_prefix_assignment_free(&(*cmd_suffix)->words);
	free(*cmd_suffix);
	*cmd_suffix = NULL;
}

int	parse_cmd_suffix(t_scanner *scanner, t_cmd_suffix **cmd_suffix)
{
	int	status;

	*cmd_suffix = ft_calloc(1, sizeof(t_cmd_suffix));
	status = cmd_suffix_add(scanner, *cmd_suffix);
	if (status == SUCCESS)
	{
		while (status == SUCCESS)
			status = cmd_suffix_add(scanner, *cmd_suffix);
		return (SUCCESS);
	}
	else
		cmd_suffix_free(cmd_suffix);
	// return (ERROR);
	return (EMPTY);
}

void	simple_cmd_free(t_simple_cmd **simple_cmd)
{
	if (!*simple_cmd)
		return ;
	cmd_prefix_free(&(*simple_cmd)->prefix);
	cmd_suffix_free(&(*simple_cmd)->suffix);
	cmd_name_free(&(*simple_cmd)->cmd_name);
	cmd_word_free(&(*simple_cmd)->cmd_word);
	free(*simple_cmd);
	*simple_cmd = NULL;
}

int	parse_simple_cmd(t_scanner *scanner, t_simple_cmd **simple_cmd)
{
	*simple_cmd = ft_calloc(1, sizeof(t_simple_cmd));
	if (parse_simple_cmd_prefix(scanner, *simple_cmd) == SUCCESS)
	{
		if (parse_cmd_suffix(scanner, &(*simple_cmd)->suffix) == ERROR)
		{
			simple_cmd_free(simple_cmd);
			return (ERROR);
		}
		else
			return (SUCCESS);
	}
	else
		simple_cmd_free(simple_cmd);
	// return (SUCCESS);
	return (ERROR);
}