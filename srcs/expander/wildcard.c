#include "expander.h"
#include <dirent.h>

char	**dir_content(const char *path)
{
	t_list			*lst_buffer;
	DIR				*dir;
	struct dirent	*dirent;

	dir = opendir(path);
	if (dir == NULL)
	{
		ms_perror(path);
		return (NULL);
	}
	lst_buffer = NULL;
	while (1)
	{
		dirent = readdir(dir);
		if (dirent == NULL)
			break ;
		ft_lstadd_back(&lst_buffer, ft_lstnew(dirent->d_name));
	}
	if (closedir(dir) == -1)
		ms_perror("closedir in dir_content");
	return ((char **)ft_lsttoaa_clear(&lst_buffer));
}

int	wildcard_substitution(t_list *lst_pattern, const char *str)
{
	const char	*find;

	if (cmp_strprefix(str, lst_pattern->content))
		return (-1);
	if (lst_pattern->next == NULL)
		return (0);
	find = &str[ft_strlen(lst_pattern->content)];
	lst_pattern = lst_pattern->next;
	while (lst_pattern->next != NULL)
	{
		find = ft_strstr(find, lst_pattern->content);
		if (find == NULL)
			return (-1);
		find += ft_strlen(lst_pattern->content);
		lst_pattern = lst_pattern->next;
	}
	if (cmp_strsuffix(find, lst_pattern->content))
		return (-1);
	return (0);
}

void	wildcard_matching(t_list *lst_pattern, char **strlist)
{
	while (*strlist != NULL)
	{
		if (wildcard_substitution(lst_pattern, *strlist) == -1)
			ft_memmove(strlist, strlist + 1,
				sizeof(char *) * (ft_strcount(strlist + 1) + 1));
		else
			strlist++;
	}
}

/*
	This should not be called when there's only one arguments?
	Nope, I can't evaluate '*' itself then
	'*' itself actually generate two argument from the lexer, funnily enough
*/
char	**wildcard(t_list *lst_pattern)
{
	char	**strlist_content;

	strlist_content = dir_content(".");
	if (((const char *)lst_pattern->content)[0] != '.')
		ft_aaremove((void **)strlist_content, cmp_strprefix, ".", NULL);
	// for (unsigned int i = 0; strlist_content[i] != NULL; i++)
	// {
	// 	const char	*colour;

	// 	if (wildcard_substitution(lst_pattern, strlist_content[i]) == -1)
	// 		colour = RED;
	// 	else
	// 		colour = GREEN;
	// 	ft_printf("%s%-18s\n"DEF, colour, strlist_content[i]);
	// }
	wildcard_matching(lst_pattern, strlist_content);
	return (strlist_content);
}
