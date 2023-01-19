#include "minishell.h"

size_t	shell_varname_len(const char *input)
{
	size_t	i;

	if (ft_isdigit(input[0]))
		return (!!ft_dprintf(2, "Digit in shell_varname_len: %s\n", input));
	i = 0;
	while (ft_isnameletter(input[i]))
		i++;
	return (i);
}

static char	*ft_substrenv(const char *start)
{
	char	*substr;
	char	*env;

	substr = ft_substr(start, 0, shell_varname_len(start));
	env = getenv(substr);
	free(substr);
	if (env == NULL)
		return (ft_strdup(""));
	else
		return (ft_strdup(env));
}

	// else if (src[1] == '#')
		/// @brief Expand to argc
		///	@note not exactly sure how to demonstrate this in terminal
	// else if (src[1] == '@')
		///	@brief Expand to every given arguments
		///	@note not exactly sure how to demonstrate this in terminal
	// else if (src[1] == '$')
	// {
		///	@brief Expand to the current pid
		///	@note Getpid is forbidden in this project
	// 	len_varname = 1;
	// 	str = ft_itoa(getpid());
	// }
	// else if (src[1] == '(')
		///	@brief Expand the printed message from the program
		///	@note Parenthesis without '$' will just execute the given command in another process
	// else if (src[1] == '{')
		///	@brief Function simillar with parsing character ("") at baseline
		//	but support certain expression such as:
		///		@example Pattern substitution: ${string//replace this/to this}
		///		@example Expand to every element in an array: ${Array[@]}
	// else if (ft_isdigit(src[1]))
		///	@brief Basically argv[digit]
		///	@note not exactly sure how to demonstrate this in terminal

char	*expander_node(char **src)
{
	char	*str;

	if ((*src)[1] == '?')
	{
		str = ft_itoa(g_last_exitstatus);
		(*src)++;
	}
	else if (!ft_isnameletter((*src)[1]))
		str = ft_strdup("$");
	else
	{
		str = ft_substrenv(&(*src)[1]);
		(*src) += shell_varname_len(&(*src)[1]);
	}
	return (str);
}

char	*ms_expander(const char *command_line)
{
	char	*var;
	char	*start;
	t_list	*lst;

	lst = NULL;
	start = (char *)command_line;
	var = ft_strchr(start, '$');
	while (var != NULL)
	{
		ft_lstadd_back(&lst, ft_lstnew(ft_substr(start, 0, var - start)));
		ft_lstadd_back(&lst, ft_lstnew(expander_node(&var)));
		start = var + 1;
		var = ft_strchr(start, '$');
	}
	ft_lstadd_back(&lst, ft_lstnew(ft_strdup(start)));
	return (ft_lsttoa_clear(&lst));
}

// Cpp insert attempt? Not even halfway close tho
// char	*ms_expander(const char *command_line)
// {
// 	char	*var;
// 	char	*tmp;
// 	char	*start;
// 	t_list	*lst_expand;
// 	size_t	len_varname;

// 	lst_expand = NULL;
// 	start = ft_strdup(command_line);
// 	tmp = start;
// 	var = ft_strchr(start, '$');
// 	while (var != NULL)
// 	{
// 		ft_lstadd_back(&lst_expand, ft_lstnew(ft_substr(start, 0, var - start)));
// 		ft_lstadd_back(&lst_expand, expander_node(var, &len_varname));
// 		start = var + len_varname + 1;
// 		var = ft_strchr(start, '$');
// 	}
// 	ft_lstadd_back(&lst_expand, ft_lstnew(ft_strdup(start)));
// 	free(tmp);
// 	return (ft_lsttoa_clear(&lst_expand));
// }

// char	*ms_expander(t_data data)
// {
// 	char	*var;
// 	char	*start;
// 	t_list	*lst_expand;
// 	size_t	len_varname;

// 	lst_expand = NULL;
// 	start = data.input_raw;
// 	var = start - 1;
// 	while (*++var != '\0')
// 	{
// 		if (*var != '$')
// 			continue ;
// 		ft_lstadd_back(&lst_expand, ft_lstnew(ft_substr(start, 0, var - start)));
// 		ft_lstadd_back(&lst_expand, expander_node(data, var, &len_varname));
// 		var += len_varname;
// 		start = var + 1;
// 	}
// 	ft_lstadd_back(&lst_expand, ft_lstnew(ft_strdup(start)));
// 	return (ft_lsttoa_clear(&lst_expand));
// }

// static int	ft_bquote(char *src)
// {
// 	char	quote_start;
// 	char	*end;

// 	if (src[0] == '\0' || !(src[0] == '\'' || src[0] == '\"'))
// 		return (0);
// 	quote_start = src[0];
// 	end = ft_memmove(src, src + 1, ft_strlen(src + 1) + 1);
// 	while (*end != '\0' && *end != quote_start)
// 	{
// 		if (quote_start != '\'' && *end == '\\')
// 			shell_backslash(end);
// 		end++;
// 	}
// 	// if (*end != quote_start)
// 	if (*end == '\0')
// 		return (1 - !ft_dprintf(2, "zsh: parse error\n"));
// 	ft_memmove(end, end + 1, ft_strlen(end + 1) + 1);
// 	return (end - src);
// }
