/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:45:20 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/19 19:24:20 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define SUCCESS 0
# define ERROR 1

# define PIPE_STAGE_1 1
# define PIPE_STAGE_2 2

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

/* define INT_MAX  */
# include <limits.h>

/* signal() */
# include <signal.h>

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
t_parser		*parser_init(t_double_list *token_list);
void			parse_token_type_reassign(t_double_list *token_list);
void			parse_token_type_same_concat(t_double_list *token_list);

/* parse_handler */
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
void			and_or_ast_attach_last(t_ast **ast_root, t_ast *new_node);

/* util_pattern_searcher */
t_ast			*pattern_searcher(t_ast *(*pattern[])(t_parser *), t_parser *p);

/* ********** EXECUTOR ********** */

/* ms_executor */
void			ms_executor(t_ast *root);
bool			is_executable(char *path_to_file);

/* execute_redir */
int	            execute_redir(t_ast *redir_node);
int				get_redir_fd(t_ast *redir_node, int redir_fd[2]);
int	            get_redir_fd_in(int redir_type, char *filename);
int	            get_redir_fd_out(int redir_type, char *filename);

/* execute_heredoc */
int	            execute_heredoc(t_ast *heredoc_node);
void	        heredoc_process(char *delimiter, char *tmp_filename);
void	        heredoc_read_input_to_file(char *delimiter, char *tmp_file_name);

/* execute_cmd */
void	        execute_cmd(t_ast *cmd_node);
int	            cmd_argc_get(t_ast *cmd_node);
char	        **cmd_argv_init(t_ast *cmd_node);

/* execute_cmd_process */
void	        cmd_child_process(t_ast *cmd_node);
void	        cmd_parent_process(pid_t child_pid);
void	        cmd_child_free(t_ast *cmd_node, char *cmd_path, char **argv, char **envp);

/* execute_pipe */
void	        execute_pipe(t_ast *pipe_node, int pipe_stage, int read_end_fd);

/* execute_job */
void	        execute_job(t_ast *job_node);

/* execute_and_or */
void	        execute_and_or(t_ast *and_or_node);

/* execute_cmdline */
void	        execute_cmdline(t_ast *cmdline_node);

/* util_tmp_filename_generator */
char	        *tmp_filename_generator(void);
char	        *tmp_filename_create(int file_num);

/* ********** SIGNALS ********** */

void	        signal_handler_heredoc(void);
void	        signal_handler_parallel_process(void);
void			signal_handler_parent_process(void);
void			signal_handler_child_process(void);

/* ********** DATA STRUCTURE ********** */

/* Double Linked List */
t_double_list	*double_lstnew(void *content);
int				double_lstsize(t_double_list *lst);
t_double_list	*double_lstlast(t_double_list *lst);
void			double_lstiter(t_double_list *lst, void (*fj)(void *));
void			double_lstadd_back(t_double_list **lst, t_double_list *new);
void			double_lstdelone(t_double_list *lst, void (*del)(void *));
void			double_lstclear(t_double_list **lst, void (*del)(void *));

/* Stack */
t_stack			*stack_create(int max);
void			stack_pop(t_stack *stack);
void			stack_free(t_stack **stack);
bool			stack_is_full(t_stack *stack);
bool			stack_is_empty(t_stack *stack);
void			stack_push(t_stack *stack, char item);

/* ********** ENVP ********** */

void			envp_free(void);
t_double_list	*envp_get(void);
t_double_list	*envp_init(char **envp);
char			*env_value_get(char *env_var);
t_double_list	*envp_set(t_double_list *envp);

/* ********** PATH ********** */

char			*absolute_path_find(char *file);
bool			file_in_path(char *dir_path, char *file);

/* ********** OTHER_UTILS ********** */

void			util_arr_str_free(void *arr_str);
void			util_perror(char *title, char *msg);
bool	        util_is_same_str(char *str1, char *str2);
char			**util_list_to_arr_str(t_double_list *list);

/* ********** DEBUG ********** */

void			debug_env_content_print(void *content);
void	        debug_print_ast(t_ast *root, int indent);
void			debug_token_content_print(void *content);
void			debug_list_content_print(t_double_list *lst, void (*f)(void *));
#endif