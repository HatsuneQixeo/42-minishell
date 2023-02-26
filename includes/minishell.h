/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:45:20 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/02/25 10:00:44 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define SUCCESS 0
# define ERROR 1

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

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>

# include "libft.h"
# include "ms_struct.h"

/* ********** TOKENIZER ********** */

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
void			rm_token_value(t_token *token);
void			list_token_type_set(t_double_list *list, t_token_type set_type);
t_token			*concat_2_tokens(t_token *t1, t_token *t2, t_token_type type);

/* ********** PARSER ********** */

t_node			*ms_parser(t_double_list *token_list);
void			parse_token_list(t_double_list *token_list);
void			parse_token_type_reassign(t_double_list *token_list);
void			parse_token_type_same_concat(t_double_list *token_list);
void			handle_quote(t_double_list *quote);
void			handle_variable(t_double_list *variable);
void			handle_backslash(t_double_list *backslash);

/* ********** EXECUTOR ********** */

void			ms_executor(t_node *root);
bool			is_executable(char *path_to_file);
void			execute_token_literal(t_token *token);

/* executor process */
void			run_parent_process_literal(void);
void			run_process_literal(char *path_name, char **cmd_line);
void			run_child_process_literal(char *path_name, char **cmd_line);

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
void			ast_free(t_node **root);
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

t_double_list	*env_init(char **envp);
char			*env_value_get(char *env_var);
t_double_list	*env_set_or_get(t_double_list *env_head);
void			env_free(t_double_list **env_list);

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
void			debug_token_content_print(void *content);
void			debug_ast_content_print(t_node *root, int depth);
void			debug_list_content_print(t_double_list *lst, void (*f)(void *));
#endif