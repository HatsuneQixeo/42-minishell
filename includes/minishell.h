/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:45:20 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/13 06:58:42 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define SUCCESS 0
# define ERROR 1
# define ERR_SYNTAX 0x0000DEAD

/* Readline function */
# include <readline/readline.h>
# include <readline/history.h>

/* opendir(), readir(), closedir() */
# include <dirent.h>

/* struct stat, stat() */
# include <sys/stat.h>

/* fork() */
# include <sys/types.h>

/* wait() */
# include <sys/wait.h>

/* open() */
# include <fcntl.h>

/* self-defined headers */
# include "libft.h"
# include "ms_struct.h"

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>

int g_exit_status;

/* ********** TOKENIZER ********** */

/* ms_tokenizer */
t_double_list	*ms_tokenizer(char *input);
t_token_type	token_type_identify(char c);
t_token			*token_create(void *value, t_token_type type);

/* utils_token_check */
bool			token_is_space(char c);
bool			token_is_redir(t_token *token);
bool			token_is_operator(t_token *token);
bool			token_is_separator(t_token *token);

/* utils_token_free */
void			token_free(void	*token);
void			token_list_free(t_double_list **token_list);
void			token_free_del(void *token, void (*del)(void *));

/* utils_token_getter_setter */
t_grammar		*token_grammar_get(void);
t_token_type	token_type_get(t_token *token);
void			*token_value_get(t_token *token);
void			token_type_set(t_token *token, t_token_type type);

/* utils_token_others */
t_token			*token_dup(t_token *token);
void			rm_token_value(t_token *token);
t_token			*concat_2_tokens(t_token *t1, t_token *t2, t_token_type type);
void			list_token_type_set(t_double_list *list, t_token_type set_type);

/* ********** PARSER ********** */

/* ms_parser */
void			parser_free(t_parser **p);
t_ast			*ms_parser(t_double_list *token_list);
void			parse_token_type_reassign(t_double_list *token_list);
void			parse_token_type_same_concat(t_double_list *token_list);
void			handle_quote(t_double_list *quote);
void			handle_variable(t_double_list *variable);
void			handle_backslash(t_double_list *backslash);
t_double_list	*tokenlist_regroup(t_double_list *token_list);
t_double_list	*tokenlist_filter(t_double_list *list, t_token_type type);

/* parse_redir */
t_ast			*parse_redir(t_parser *p);
t_ast			*parse_redir_in(t_parser *p);
t_ast			*redir_in_pattern_1_heredoc(t_parser *p);
t_ast			*redir_in_pattern_2_infile(t_parser *p);
t_ast			*redir_out_pattern_1_append(t_parser *p);
t_ast			*redir_out_pattern_2_outfile(t_parser *p);
t_ast			*parse_redir_out(t_parser *p);

/* parse_tokenlist */
t_ast			*node_init(t_asttype node_type);
t_ast			*parse_tokenlist(t_parser *p);
t_ast			*tokenlist_pattern_3_args(t_parser *p);
t_ast			*tokenlist_pattern_2_redir(t_parser *p);
t_ast			*tokenlist_pattern_1_cmd_name(t_parser *p);

/* parse_cmd */
t_ast			*parse_cmd(t_parser *p);
t_ast			*cmd_pattern_1_tokenlist(t_parser *p);

void			debug_print_ast(t_ast *root, int indent);
/* parse_job */
t_ast			*parse_job(t_parser *p);
t_ast			*job_pattern_1_subshell_pipe(t_parser *p);
t_ast			*job_pattern_2_cmd_pipe(t_parser *p);
t_ast			*job_pattern_3_subshell(t_parser *p);
t_ast			*job_pattern_4_cmd(t_parser *p);

/* parse_and_or */
t_ast			*parse_and_or(t_parser *p);
t_ast			*and_or_node_init(int node_type, t_ast *attach_left_node);
t_ast			*and_or_pattern_1_and(t_parser *p);
t_ast			*and_or_pattern_2_or(t_parser *p);
t_ast			*and_or_pattern_3_job(t_parser *p);
t_ast			*and_or_pattern_4_cmd_line_and(t_parser *p);
t_ast			*and_or_pattern_5_cmd_line_or(t_parser *p);
t_ast			*and_or_pattern_6_cmd_line(t_parser *p);

/* parse_cmdline */
t_ast			*parse_cmdline(t_parser *p);
t_ast			*cmd_line_pattern_1_andor_cmdline(t_parser *p);
t_ast			*cmd_line_pattern_2_andor_seq(t_parser *p);
t_ast			*cmd_line_pattern_3_andor(t_parser *p);

/* util_scanner */
void			s_free(t_scanner **scanner);
t_double_list	*s_next(t_scanner *scanner);
t_token			*s_get_token(t_scanner *scanner);
t_scanner		*s_init(t_double_list *token_list);
bool			s_token_type_matches(t_token_type type, t_scanner *s);
bool			s_match_and_consume_token(t_token_type type, t_scanner *s);

/* util_ast */
void			ast_delete(t_ast **node);
int				ast_gettype(t_ast *node);
void			ast_setdata(t_ast *node, char *data);
void			ast_settype(t_ast *node, t_asttype type);
void			cmd_ast_insert_left(t_ast *root, t_ast *node);
void			cmd_ast_insert_right(t_ast *root, t_ast *node);
void			ast_attach(t_ast *root, t_ast *left, t_ast *right);
void			and_or_ast_insert_top(t_ast **ast_root, t_ast *new_node);
void			and_or_ast_insert_last(t_ast **ast_root, t_ast *new_node);

/* util_pattern_searcher */
t_ast			*pattern_searcher(t_ast *(*pattern[])(t_parser *), t_parser *p);

/* ********** EXECUTOR ********** */

void			ms_executor(t_node *root);
bool			is_executable(char *path_to_file);
void			execute_token_literal(t_token *token);

/* executor process */
void			run_parent_process_literal(void);
void			run_process_literal(char *path_name, char **cmd_line);
void			run_child_process_literal(char *path_name, char **cmd_line);

/* ms_executor */
void	        ms_executor_prototype(t_ast *root);

/* ********** DATA STRUCTURE ********** */

/* Double Linked List */
t_double_list	*double_lstnew(void *content);
int				double_lstsize(t_double_list *lst);
t_double_list	*double_lstlast(t_double_list *lst);
void			double_lstiter(t_double_list *lst, void (*fj)(void *));
void			double_lstadd_back(t_double_list **lst, t_double_list *new);
void			double_lstdelone(t_double_list *lst, void (*del)(void *));
void			double_lstclear(t_double_list **lst, void (*del)(void *));

/* Abstract Syntax Tree*/
void			ast_create(t_node **root, t_double_list *token_list);
void			ast_add_token_operator(t_node **root, t_token *token);
void			ast_add_token_literal(t_node **root, t_double_list *list);
void			ast_del_content_token(void *token);

/* Binary Tree */
t_node			*btree_node_init(void *content);
void			btree_node_add(t_node **parent, t_node *node);
void			btree_free(t_node **node, void (*del)(void *));

/* Stack */
t_stack			*stack_create(int max);
void			stack_pop(t_stack *stack);
void			stack_free(t_stack **stack);
bool			stack_is_full(t_stack *stack);
bool			stack_is_empty(t_stack *stack);
void			stack_push(t_stack *stack, char item);

/* ********** ENVIRONMENT VARIABLE POINTER ********** */

t_double_list	*envp_get(void);
t_double_list	*envp_init(char **envp);
char			*env_value_get(char *env_var);
void			envp_free(t_double_list **env_list);
t_double_list	*envp_set(t_double_list *envp);

/* ********** PATH ********** */

char			*absolute_path_find(char *file);
bool			file_in_path(char *dir_path, char *file);

/* ********** UTILS ********** */

void			util_clear_screen(void);
void			util_arr_str_free(void *arr_str);
void			util_perror(char *title, char *msg);
char			**util_list_to_arr_str(t_double_list *list);

/* ********** DEBUG ********** */

void			debug_env_content_print(void *content);
void	        debug_print_ast(t_ast *root, int indent);
void			debug_token_content_print(void *content);
void			debug_ast_content_print(t_node *root, int depth);
void			debug_list_content_print(t_double_list *lst, void (*f)(void *));
#endif