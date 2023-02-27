#include "builtin.h"

int	ft_isnameend(int c)
{
	return (c == '\0' || c == '=');
}

int	cmp_strvarname(const void *str, const void *varname)
{
	const char	*it_str = str;
	const char	*it_varname = varname;
	size_t		i;

	i = 0;
	while (it_str[i] == it_varname[i] && !ft_isnameend(it_str[i]))
		i++;
	if (ft_isnameend(it_str[i]) && ft_isnameend(it_varname[i]))
		return (0);
	return (it_str[i] - it_varname[i]);
}
