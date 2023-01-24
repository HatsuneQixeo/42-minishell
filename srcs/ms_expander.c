#include "minishell.h"

static size_t	shell_varname_len(const char *input)
{
	size_t	i;

	if (ft_isdigit(input[0]))
		return (!!ft_dprintf(2, "Digit in shell_varname_len: %s\n", input));
	i = 0;
	while (ft_isnameletter(input[i]))
		i++;
	return (i);
}

static char	*ft_substrenv(char **src)
{
	char	*substr;
	char	*env;
	size_t	len;

	len = shell_varname_len(&(*src)[1]);
	substr = ft_substr((*src), 1, len);
	(*src) += len;
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

static char	*expander_node(char **src)
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
		str = ft_substrenv(src);
	return (str);
}

char	*ms_expander(const char *command_line)
{
	char	*var;
	t_list	*lst;
	int		inside_doublequote;

	lst = NULL;
	var = (char *)command_line - 1;
	inside_doublequote = 0;
	while (*++var != '\0')
	{
		if (*var == '\'' && inside_doublequote == 0)
		{
			var = ft_strchr(var + 1, '\'');
			if (var == NULL)
				break ;
		}
		else if (*var == '\"')
			inside_doublequote = !inside_doublequote;
		if (*var != '$')
			continue ;
		ft_lstadd_back(&lst, ft_lstnew(ft_substr(command_line, 0, var - command_line)));
		ft_lstadd_back(&lst, ft_lstnew(expander_node(&var)));
		command_line = var + 1;
	}
	ft_lstadd_back(&lst, ft_lstnew(ft_strdup(command_line)));
	return (ft_lsttoa_clear(&lst));
}
