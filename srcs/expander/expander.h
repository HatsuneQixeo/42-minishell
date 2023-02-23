#ifndef EXPANDER_H
# define EXPANDER_H

# include "token.h"
# include "ms_common.h"

char	*ft_getenv(char **envp, const char *varname);
char	*expand_var(char **envp, const char **p_src);
t_list	*expand_arg(char **envp, const char *arg);

typedef t_list	*(t_ftexpand)(char **envp, t_token *token);

t_list	*expand_lst_argv(char **envp, t_token *token);
t_list	*expand_lst_rdrt(char **envp, t_token *token);

t_list	*ms_expander(char **envp, t_list *lst, t_ftexpand ft_expand);

#endif

