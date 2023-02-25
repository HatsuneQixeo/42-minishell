#ifndef PARSER_H
# define PARSER_H

# include "ms_common.h"
# include "ctrl.h"

int		heredoc_limiter(char *limiter);
t_list	*heredoc(const char *limiter);

int		parser_syntax(t_list *lst_token);

t_list	*ms_parser(t_list **lst_token);

#endif
