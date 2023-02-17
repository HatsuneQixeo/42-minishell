#include "minishell.h"

int	ctrl_any(void)
{
	return (1);
}

// ;
int	ctrl_wait(void)
{
	return (1);
}

int	ctrl_success(void)
{
	return (g_lastexit == 0);
}

int	ctrl_failure(void)
{
	return (g_lastexit != 0);
}
