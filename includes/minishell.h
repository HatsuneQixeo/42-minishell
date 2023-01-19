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

# include "stack.h"
# include "node.h"

# include "shell_utils.h"

# include "executor.h"
# include "pipex.h"

typedef struct
{
	char	*input_raw;
	char	*input_expanded;
	char	**prg_argv;
	char	**envp;
}			t_data;


u_char	g_last_exitstatus;
/* signals */
void	ms_signals_handler(void);

/* routine */
void	ms_input(char **envp);
char	*expander_node(char **src);

/* env_utils */

#endif