/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:21:06 by hqixeo            #+#    #+#             */
/*   Updated: 2023/03/07 15:22:08 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "expander.h"

static char	*expand_dquote(char **envp, const char **p_it)
{
	t_list		*lst;
	const char	*it = (*p_it)++;

	lst = NULL;
	while (*++it != '\"')
	{
		if (*it != '$')
			continue ;
		if (it != *p_it)
			ft_lstadd_back(&lst, ft_lstnew(ft_substr(*p_it, 0, it - *p_it)));
		if (ft_isquote(*(it + 1)))
			ft_lstadd_back(&lst, ft_lstnew(ft_strdup("$")));
		else
			ft_lstadd_back(&lst, ft_lstnew(expand_var(envp, &it)));
		*p_it = it + 1;
	}
	if (it != *p_it)
		ft_lstadd_back(&lst, ft_lstnew(ft_substr(*p_it, 0, it - *p_it)));
	*p_it = it;
	return (ft_lsttostr_clear(&lst));
}

static char	*expand_skipquote(const char **p_it, char quote)
{
	const char	*end = ft_strchr(&(*p_it)[1], quote);
	char		*substr;

	substr = ft_substr(&(*p_it)[1], 0, end - &(*p_it)[1]);
	*p_it = end;
	return (substr);
}

/**
 * @brief 
 * If the 2d array contain more than one string,
 * 	which is when the expanded variable contain ISSPACE (Hatsune(Space)Miku),
 * 	it will move the buffer into the give linked list,
 * 	and append the list with the rest of the string
 * The last string in the 2d array will be the new buffer
 * 
 * 
 * @param lst_argv 
 * @param strlist 
 * @param p_buffer 
 */
static void	ass_pain_append(t_list **lst_argv, char **strlist, char **p_buffer)
{
	int		i;

	if (strlist[0] == NULL)
		return ;
	/* Need to evaluate every strlist before adding to the list or joining */
	*p_buffer = ft_strcombine(*p_buffer, strlist[0]);
	i = 0;
	while (strlist[++i] != NULL)
	{
		ft_lstadd_back(lst_argv, ft_lstnew(*p_buffer));
		*p_buffer = strlist[i];
	}
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
 * (Refer to ass_pain_append for this section)
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

	expand_value = expand_var(envp, p_it);
	if (expand_value == NULL)
		return ;
	/* if expand value has space in the front, do not join */
	/* Oh my spagetti, I have to refactor this sooner or later */
	/* Oh my dumbass, I think the refactor version is not solving anything */
	strlist = ft_split_is(expand_value, ft_isspace);
	/*
		Maybe I should expand the wildcard here ?
		But I have no idea whether the previous * is literal character
		Which is why I'm expanding the strlist ?
		The wildcard also need to take the buffer as part of the argument
	*/
	free(expand_value);
	ass_pain_append(lst_argv, strlist, p_buffer);
	free(strlist);
}

/**
 * @test
 * $INVALID			should return an empty list (This, this is a pain in the ass)
 * $UNQUOTESPACE	should return multiple argv
 * 
 * Currently functional version
 */
t_list	*expand_str(char **envp, const char *arg)
{
	t_list		*lst_argv;
	const char	*it = arg - 1;
	char		*buffer;

	lst_argv = NULL;
	buffer = NULL;
	while (*++it != '\0')
	{
		if (!(*it == '\'' || *it == '\"' || *it == '$'))
			continue ;
		if (it != arg)
			buffer = ft_strcombine(buffer, ft_substr(arg, 0, it - arg));
		if (*it == '\'')
			buffer = ft_strcombine(buffer, expand_skipquote(&it, *it));
		else if (*it == '\"')
			buffer = ft_strcombine(buffer, expand_dquote(envp, &it));
		else if (*it == '$')
			bash_expand_ass_pain(&lst_argv, envp, &it, &buffer);
		arg = it + 1;
	}
	if (it != arg)
		buffer = ft_strcombine(buffer, ft_substr(arg, 0, it - arg));
	if (buffer != NULL)
		ft_lstadd_back(&lst_argv, ft_lstnew(buffer));
	// lstshow_name("buffer");
	// ft_lstiter(lst_argv, lstshow_str);
	return (lst_argv);
}
