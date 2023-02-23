#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

typedef int	(*t_ftbuiltin)(char **argv, t_data *data);

int	ms_cd(char **argv, t_data *data);
int	ms_echo(char **argv, t_data *data);
int	ms_env(char **argv, t_data *data);
int	ctrl_(char **argv, t_data *data);
int	ms_export(char **argv, t_data *data);
int	ms_pwd(char **argv, t_data *data);
int	ms_unset(char **argv, t_data *data);

#endif
