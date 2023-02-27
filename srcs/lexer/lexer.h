#ifndef LEXER_H
# define LEXER_H

# include "ms_common.h"
# include "token.h"

char	*ms_closequote(const char *raw);
/* Lexer */
t_list	*ms_lexer(const char *raw);

#endif
