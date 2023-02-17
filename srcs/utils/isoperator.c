#include "minishell.h"

int	isoperator_ctrl(enum e_tokentype type)
{
	return (type == CTRL);
}

int	isoperator_rdrt(enum e_tokentype type)
{
	return (type == RDRT);
}

int	isoperator_subsh(enum e_tokentype type)
{
	return (type == SUBSH_BEGIN || type == SUBSH_END);
}
