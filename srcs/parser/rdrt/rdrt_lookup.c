#include "rdrt.h"

static int	rdrt_cmpft(const t_rdrt *ref1, const t_rdrt *ref2)
{
	return (ref1->ft_rdrt != ref2->ft_rdrt);
}

static int	rdrt_cmpvalue(const t_rdrt *ref1, const t_rdrt *ref2)
{
	return (ft_strcmp(ref1->token_arg, ref2->token_arg));
}

typedef int	(*t_getrdrt)(const t_rdrt *ref1, const t_rdrt *ref2);

static const t_rdrt	*rdrt_search(const t_rdrt *ref, t_getrdrt ft_get)
{
	static const t_rdrt	arr_rdrt[] = {
	{rdrt_heredoc, "<<", NULL},
	{rdrt_append, ">>", NULL},
	{rdrt_input, "<", NULL},
	{rdrt_overwrite, ">", NULL},
	};
	int					i;

	i = sizeof(arr_rdrt) / sizeof(arr_rdrt[0]);
	while (i--)
	{
		if (!ft_get(&arr_rdrt[i], ref))
			return (&arr_rdrt[i]);
	}
	return (NULL);
}

t_ftrdrt	rdrt_getft(const char *value)
{
	const t_rdrt	*find= rdrt_search(
				&(t_rdrt){NULL, (char *)value, NULL}, rdrt_cmpvalue);

	if (find != NULL)
		return (find->ft_rdrt);
	ft_dprintf(2, "rdrt_getft does not recognize: %s\n", value);
	return (NULL);
}

const char	*rdrt_getvalue(t_ftrdrt ft_rdrt)
{
	const t_rdrt	*find = rdrt_search(
				&(t_rdrt){ft_rdrt, NULL, NULL}, rdrt_cmpft);

	if (find != NULL)
		return (find->token_arg);
	ft_dprintf(2, "rdrt_getvalue does not recognize: %p\n", ft_rdrt);
	return (NULL);
}
