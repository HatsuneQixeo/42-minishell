#include "minishell.h"

void	lstshow_tmpname(t_list *lst, t_ftsetname ft_setname,
			const char *tmpname,t_ftlstiter ft_debug)
{
	const char	*name = ft_setname(NULL);

	ft_setname(tmpname);
	ft_lstiter(lst, ft_debug);
	ft_setname(name);
}
