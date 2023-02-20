#include "minishell.h"

size_t	shell_varname_len(const char *src)
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
char	*ms_substr_varname(const char *src)
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
char	*ft_substrenv(char **envp, const char **p_src)
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

static char	*parse_doublequote(char **envp, const char **p_it)
{
	t_list		*lst;
	const char	*it = (*p_it)++;

	lst = NULL;
	while (*++it != '\"')
	{
		if (*it != '$')
			continue ;
		ft_lstadd_back(&lst, ft_lstnew(ft_substr(*p_it, 0, it - *p_it)));
		ft_lstadd_back(&lst, ft_lstnew(expander_node(envp, &it)));
		*p_it = it + 1;
	}
	ft_lstadd_back(&lst, ft_lstnew(ft_substr(*p_it, 0, it - *p_it)));
	*p_it = it;
	return (ft_lsttostr_clear(&lst));
}

static char	*parse_singlequote(const char **p_it)
{
	const char	*end = ft_strchr(&(*p_it)[1], '\'');
	char		*substr;

	substr = ft_substr(&(*p_it)[1], 0, end - &(*p_it)[1]);
	*p_it = end;
	return (substr);
}

/**
 * @brief Imagine letting one function do only one thing
 * sounds as cringe as a="ho hi'"; ec$a expand to [0]echo [1]hi'
 * @example
 * $USER=Hatsune Miku
 * Let's assume the given variables looks like this for explanation:
 * 	lst_argv = NULL
 * 	default envp as the program received
 * 	p_it = &it ("$USER")
 * 	p_buffer = &buffer ("I_love_")
 * 
 * 	First, this function expand $USER and move the iterator to R,
 * 	the R will later be exclude by ++it in the loop outside this function
 * 
 * It then split the expand value into a 2d array {"Hatsune", "Miku"},
 * 	and combine the first string with the buffer in p_buffer
 * 	buffer = "I_love_Hatsune"
 * 
 * If the 2d array contain more than one string,
 * 	which is when the expanded variable contain ISSPACE (Hatsune(Space)Miku),
 * 	it will move the buffer into the give linked list,
 * 	and append the list with the rest of the string
 * 
 * The last string in the 2d array will be the new buffer
 * 
 * So in this case, the variables looks like follow:
 * 	lst_argv contain a node with content: "I_love_Hatsune"
 * 	envp is left unmodified, of course
 * 	The iterator pointed by p_it will be: R
 * 	The buffer pointed by p_buffer will be: "Miku"
 * 
 * @remark
 * If you find this function disgusting, I'm sorry, blame sean for that
 * @param lst_argv For appending the lst if there is multiple string from split
 * @param envp Sources for variable expansion
 * @param p_it For reading and moving the iterator
 * @param p_buffer For appending the buffer and potentially put into the lst
 */
static void	bash_expand_ass_pain(t_list **lst_argv, char **envp,
			const char **p_it, char **p_buffer)
{
	char	*expand_value;
	char	**strlist;
	int		i;

	expand_value = expander_node(envp, p_it);
	strlist = ft_split_is(expand_value, ft_isspace);
	free(expand_value);
	*p_buffer = ft_strcombine(*p_buffer, strlist[0]);
	if (strlist[1] != NULL)
	{
		ft_lstadd_back(lst_argv, ft_lstnew(*p_buffer));
		i = 0;
		while (strlist[++i + 1] != NULL)
			ft_lstadd_back(lst_argv, ft_lstnew(strlist[i]));
		*p_buffer = strlist[i];
	}
	free(strlist);
}

/**
 * @brief What should this return,
 * 	I cannot assume the return value is exactly one arg
 * Maybe the return list should be the representation of argc?
 * 
 * @param envp 
 * @param arg 
 * @return t_list* 
 */
t_list	*ms_expand_arg(char **envp, const char *arg)
{
	t_list		*lst_argv;
	const char	*it = arg - 1;
	char		*buffer;

	lst_argv = NULL;
	buffer = NULL;
	while (*++it != '\0')
	{
		if (*it == '\'')
		{
			buffer = ft_strcombine(buffer, ft_substr(arg, 0, it - arg));
			buffer = ft_strcombine(buffer, parse_singlequote(&it));
		}
		else if (*it == '\"')
		{
			buffer = ft_strcombine(buffer, ft_substr(arg, 0, it - arg));
			buffer = ft_strcombine(buffer, parse_doublequote(envp, &it));
		}
		else if (*it == '$')
			bash_expand_ass_pain(&lst_argv, envp, &it, &buffer);
	}
	ft_lstadd_back(&lst_argv, ft_lstnew(buffer));
	return (lst_argv);
}

/**
 * @brief Likely will be abandoned
 * 	due to not being able to communicate literal character
 * 	like ' and " inside the variable,
 * 	which I'm not sure If I really want to let my lexer to deal with this
 * 
 * @param envp 
 * @param command_line 
 * @return char* 
 */
// char	*ms_expander(char **envp, const char *command_line)
// {
// 	t_list		*lst;
// 	const char	*it = command_line - 1;
// 	int			inside_doublequote;

// 	lst = NULL;
// 	inside_doublequote = 0;
// 	while (*++it != '\0')
// 	{
// 		if (*it == '\"')
// 			inside_doublequote = !inside_doublequote;
// 		else if (inside_doublequote)
// 			;
// 		else if (*it == '\'')
// 			it = ft_strchr(it + 1, '\'');
// 		else if (*it == '*')
// 		{
// 			ft_printf("Wildcard substitution\n");
// 		}
// 		if (*it != '$')
// 			continue ;
// 		ft_lstadd_back(&lst, ft_lstnew(ft_substr(command_line, 0, it - command_line)));
// 		ft_lstadd_back(&lst, ft_lstnew(expander_node(envp, &it)));
// 		command_line = it + 1;
// 	}
// 	ft_lstadd_back(&lst, ft_lstnew(ft_strdup(command_line)));
// 	return (ft_lsttostr_clear(&lst));
// }
