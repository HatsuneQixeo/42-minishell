/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_common.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 00:52:27 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/02/26 18:52:50 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_COMMON_H
# define MS_COMMON_H

# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>

# define MINISHELL	"🐚"
int	g_lastexit;

typedef struct s_data
{
	char	**envp;
}			t_data;


int		ft_isquote(int c);
int		ft_isnameletter(int c);
int		ft_dup3(int fd_attribute, int fd_value);
int		ms_errlog(const char *str, ...);
void	ms_perror(const char *name);

/* Forbidden */
void	leakcheck(const char *str);
void	leakfd(const char *str);
void	debug_errno(const char *name);
void	lstshow_tmpname(t_list *lst, t_ftsetname ft_setname,
			const char *tmpname, t_ftiterlst ft_debug);

#endif
