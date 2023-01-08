/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 17:11:38 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/01/09 00:47:15 by ntan-wan         ###   ########.fr       */
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

# include "stack.h"
# include "node.h"
# include "token.h"

typedef struct s_env
{
	char	**envp;
	char	**vars;
	char	*pwd;
	char	*oldpwd;
}	t_env;

/* signals */
void	ms_signals_handler(void);

/* routine */
void	ms_routine_run(void);

/* env_utils */
t_env	*ms_env_init(char **envp);
void	ms_env_free(t_env **environment);

/* parens_check */
bool	is_balanced_parens(char *str);

/* lexer */
void    ms_lexer(char *input);

/* other utils */
void	util_clear_screen(void);
char	**util_str_arr_dup(char **arr);
void	*util_realloc(void *ptr, size_t old_size, size_t new_size);
#endif