/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 17:11:38 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/01/09 03:09:59 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <signal.h>
# include <stdio.h>

# include <readline/readline.h>
# include <readline/history.h>

# include "shell_utils.h"
# include "pipex.h"

# define MINISHELL	"🐚"

int			g_lastexit;
typedef int	(*t_ftexitstatus)(void);

enum e_tokentype
{
	DEFAULT,
	RDRT,
	CTRL,
	SUBSH_BEGIN,
	SUBSH_END,
	TOKENCOUNT
};

typedef struct s_token
{
	enum e_tokentype	type;
	char				*value;
}			t_token;

typedef const t_token	t_tokenlist[];
typedef int	(*t_ftexe)(char **envp, t_list *lst, int fd_in, int fd_out);

typedef struct s_control
{
	t_ftexitstatus	condition;
	/**
	 * @brief Question:
	 * What should this ptr point to
	 * ex: Like a lst of arguments, like lst_exe
	 * ex: or a subshell, how should I act is this is subsh
	 * What if this is a function take takes in a linked list?
	 * That solves it?
	 */
	t_ftexe			ft_exe;
	t_list			*lst_exe;
	/* (cat) < infile? This count as a cmd block no? */
	t_list			*rdrt_token;
}			t_ctrl;

typedef struct s_data
{
	char	**envp;
}			t_data;

/* signals */
void	ms_signals_handler(void);

/* Exit Status */
int		ctrl_any(void);
int		ctrl_success(void);
int		ctrl_failure(void);

/* Isoperator */
int		isoperator_ctrl(enum e_tokentype type);
int		isoperator_rdrt(enum e_tokentype type);
int		isoperator_subsh(enum e_tokentype type);

/* routine */
void	ms_input(char **envp);

char	*ms_closequote(const char *raw);

/* Token */
t_token	*token_new(char *str, enum e_tokentype type);
void	del_token(void *content);
const char	*lstiter_tokenname(const char *newname);
void	lstiter_showtoken(int i, void *content);

/* Control Structure*/
const char	*ctrl_name(t_ftexitstatus condition);
void	show_ctrl(t_list *lst_ctrl);
// void	lstiter_showctrl(int i, void *content);
void	del_ctrl(void *content);
t_list	*ms_control_structure(const char *input_raw);
t_list	*ms_control_token(const char *input_raw);

/* Parser */
int		parser_syntax(t_list *lst_token);

/* Lexer */
t_list	*ms_lexer(const char *input_raw);

/* Expand? */
size_t	shell_varname_len(const char *src);
char	*ms_substr_varname(const char *src);
char	*ft_substrenv(char **envp, const char **p_src);
char	*expander_node(char **envp, const char **p_src);
t_list	*ms_expand_arg(char **envp, const char *arg);
char	*ms_expander(char **envp, const char *command_line);

/* env_utils */

/* Exe */

/* Currently only serves as an idenfitier */
int	exe_argv(char **envp, t_list *lst_argv, int fd_in, int fd_out);
/* Currently only serves as an idenfitier */
int	exe_subsh(char **envp, t_list *lst_ctrl, int fd_in, int fd_out);
#endif