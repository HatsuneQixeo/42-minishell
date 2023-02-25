/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdrt.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:21:08 by hqixeo            #+#    #+#             */
/*   Updated: 2023/02/25 10:21:08 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RDRT_H
# define RDRT_H

# include "ms_common.h"
# include "expander.h"

# define HEREDOC_TXT	".miniheredoc.miku.is.cute.tmp"

# define READ_END	0
# define WRITE_END	1

typedef struct s_rdrt	t_rdrt;
typedef int				(*t_ftrdrt)(char **envp, t_rdrt *rdrt);

struct s_rdrt
{
	t_ftrdrt	ft_rdrt;
	char		*str_arg;
	t_list		*lst_value;
};

int	rdrt_ambiguous(const t_list *lst_value, const char *str_arg);
int			rdrt_core(const char *path, int std_fd, int option, ...);

const char	*lstname_rdrt(const char *newname);
void		lstshow_rdrt(int i, void *content);

t_ftrdrt	rdrt_getft(const char *value);
const char	*rdrt_getvalue(t_ftrdrt ft_rdrt);
t_rdrt		*rdrt_new(t_ftrdrt ft_rdrt, char *str_arg);
void		del_rdrt(void *content);

int			rdrt_heredoc(char **envp, t_rdrt *rdrt);
int			rdrt_quotedheredoc(char **envp, t_rdrt *rdrt);
int			rdrt_append(char **envp, t_rdrt *rdrt);
int			rdrt_input(char **envp, t_rdrt *rdrt);
int			rdrt_overwrite(char **envp, t_rdrt *rdrt);

#endif
