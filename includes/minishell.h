/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:45:20 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/02/21 02:12:48 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "ms_token.h"
# include "ms_btree.h"
# include "ms_ast.h"

# include "ms_parser.h"

typedef struct s_env
{
        char    **envp;
        char    **vars;
        char    *pwd;
        char    *oldpwd;
}       t_env;
#endif