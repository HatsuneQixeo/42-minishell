#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

typedef int	(*t_ftbuiltin)(int argc, char **argv, t_data *data);

int	ms_cd(int argc, char **argv, t_data *data);
int	ms_echo(int argc, char **argv, t_data *data);
int	ms_env(int argc, char **argv, t_data *data);
int	ctrl_(int argc, char **argv, t_data *data);
int	ms_export(int argc, char **argv, t_data *data);
int	ms_pwd(int argc, char **argv, t_data *data);
int	ms_unset(int argc, char **argv, t_data *data);

#endif