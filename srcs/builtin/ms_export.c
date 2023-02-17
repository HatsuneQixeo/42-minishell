#include "minishell.h"

/**
 * @brief 
 * @test =a, a, a=, "a ", "a ="
 * @param str 
 * @return int 
 */
static int	isvalid_identifier(const char *str)
{
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	while (ft_isnameletter(*str))
		str++;
	return (*str == '\0' || *str == '=');
}

static void	export(t_list **lst_buffer, char **envp, const char *arg)
{
	const char	*assignment = ft_strchr(arg, '=');
	char		*var_name;
	char		**existing_var;

	if (assignment == NULL)
		return ;
	var_name = ft_substr(arg, 0, (assignment + 1) - arg);
	existing_var = ft_strlistfind_prefix(envp, var_name);
	free(var_name);
	if (existing_var == NULL)
		ft_lstadd_back(lst_buffer, ft_lstnew(ft_strdup(arg)));
	else
	{
		free(*existing_var);
		*existing_var = ft_strdup(arg);
	}
}

// Let's say MIKU=Hatsune Miku, why does export $MIKU=$MIKU result in Miku=Hatsune but IKU=$MIKU result in IKU=Hatsune Miku in bash
/* Export empty argument in bash */
int	ms_export(int argc, char **argv, t_data *data)
{
	t_list	*lst_buffer;
	int		retval;

	lst_buffer = NULL;
	retval = 0;
	while (*++argv != NULL)
	{
		if (!isvalid_identifier(*argv))
		{
			ft_dprintf(2, MINISHELL": export: %s: not a valid identifier\n", *argv);
			retval = 1;
		}
		else
			export(&lst_buffer, data->envp, *argv);
	}
	if (lst_buffer != NULL)
		data->envp = ft_strlistcombine(data->envp, (char **)ft_lsttoaa_clear(&lst_buffer));
	return (retval);
}
