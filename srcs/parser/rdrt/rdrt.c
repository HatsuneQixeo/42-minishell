#include "rdrt.h"

void	lstiter_showrdrt(int i, void *content)
{
	const t_rdrt	*rdrt = content;

	rdrt_getvalue(rdrt->ft_rdrt);
	debuglst_tmpname(rdrt->lst_value, )
}

t_rdrt	*rdrt_new(t_ftrdrt ft_rdrt, char *str_arg)
{
	t_rdrt	*rdrt;

	rdrt = malloc(sizeof(t_rdrt));
	if (rdrt == NULL)
		return (NULL);
	rdrt->ft_rdrt = ft_rdrt;
	rdrt->token_arg = str_arg;
	rdrt->lst_value = NULL;
	return (rdrt);
}

void	del_rdrt(void *content)
{
	t_rdrt	*rdrt;

	rdrt = content;
	free(rdrt->token_arg);
	ft_lstclear(&rdrt->lst_value, free);
	free(rdrt);
}
