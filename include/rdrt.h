#ifndef RDRT_H
# define RDRT_H

typedef struct s_token t_token;

typedef int	(*ft_rdrt)(t_token *token);

int	rdrt_heredoc(t_token *token);
int	rdrt_append(t_token *token);
int	rdrt_input(t_token *token);
int	rdrt_overwrite(t_token *token);

#endif