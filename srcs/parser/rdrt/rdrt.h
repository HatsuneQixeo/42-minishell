#ifndef RDRT_H
# define RDRT_H

# include "token.h"
# include "ms_common.h"

typedef struct s_rdrt	t_rdrt;
typedef int	(*t_ftrdrt)(t_rdrt *rdrt);

struct s_rdrt
{
	t_ftrdrt	ft_rdrt;
	char		*token_arg;
	t_list		*lst_value;
};

t_ftrdrt	rdrt_getft(const char *value);
const char	*rdrt_getvalue(t_ftrdrt ft_rdrt);
t_rdrt		*rdrt_new(t_ftrdrt ft_rdrt, char *str_arg);
void		del_rdrt(void *content);

int			rdrt_heredoc(t_rdrt *rdrt);
int			rdrt_append(t_rdrt *rdrt);
int			rdrt_input(t_rdrt *rdrt);
int			rdrt_overwrite(t_rdrt *rdrt);

#endif
