#include "minishell.h"

static size_t	shell_varname_len(const char *src)
{
	size_t	i;

	i = 0;
	while (ft_isnameletter(src[i]))
		i++;
	return (i);
}

/**
 * @brief Substr the $MIKU from "$MIKU/iscute"
 * 
 * @param src ptr to '$'
 * @return char* $MIKU/iscute -> MIKU
 * @bug It will assume the first character is '$'
 * 	and not do any additional checking
 */
static char	*ms_substr_varname(const char *src)
{
	return (ft_substr(&src[1], 0, shell_varname_len(&src[1])));
}

/**
 * @brief Substr the env value of the given str,
 * 	also move the ptr to the end of the variable name
 * 
 * @param envp 
 * @param p_src 
 * @return char* 
 */
static char	*ft_substrenv(char **envp, const char **p_src)
{
	char	*str_varname;
	char	*str_varvalue;

	str_varname = ms_substr_varname(*p_src);
	(*p_src) += ft_strlen(str_varname);
	str_varvalue = ft_getenv(envp, str_varname);
	free(str_varname);
	if (str_varvalue == NULL)
		return (NULL);
	else
		return (ft_strdup(str_varvalue));
}

/**
 * @brief For expanding an iterator pointing to '$' character
 * 
 * @param envp 
 * @param p_src 
 * @return char* 
 */
char	*expander_node(char **envp, const char **p_src)
{
	const char	chr = (*p_src)[1];

	if (chr == '?')
	{
		(*p_src)++;
		return (ft_itoa(g_lastexit));
	}
	else if (chr == '\0')
		return (ft_strdup("$"));
	else if (!ft_isnameletter(chr))
		return (ft_strdup(""));
	else if (ft_isdigit(chr))
	{
		(*p_src)++;
		return (ft_strdup(""));
	}
	else
		return (ft_substrenv(envp, p_src));
}
