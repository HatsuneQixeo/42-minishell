/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_other_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 12:05:17 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/01/09 03:29:34 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isnameletter(int c)
{
	return (ft_isalnum(c) || c == '_');
}

void	ft_clear_screen(void)
{
	ft_printf("\e[1;1H\e[2J");
}

// echo '\\' > \\
// echo "\\" > \
// str[1] == '\n' might need to call another readline instead
void	shell_backslash(char *str)
{
	if (str[0] != '\\')
		return ;
	// It is '\0' instead of '\n' because readline terminated the '\n' character
	// else if (str[1] == '\0')
		// Readline and join and dynamic allocation blablabla 
		/// @note I think I will regret this
	// else if (str[1] == '\n')
	// 	ft_memmove(str, str + 2, ft_strlen(str + 2) + 1);
	else
		ft_memmove(str, str + 1, ft_strlen(str + 1) + 1);
}

void	ms_pathaccess(char **executable)
{
	char	*joined;
	char	**path;
	size_t	y;

	y = 0;
	path = ft_split(getenv("PATH"), ':');
	while (path[y] != NULL)
	{
		joined = ft_strinsert(path[y++], "/", *executable);
		if (!access(joined, F_OK | X_OK))
		{
			ft_strlistclear(path);
			free(*executable);
			*executable = joined;
			return ;
		}
		free(joined);
	} 
}

// Execve seem to be able to differentiate Absolute path and Relative path
// , But not program stored in PATH environmental variable
///	@note On second thought, ft_execve already handled this
// void	ms_executablepath(char **ptr_executable)
// {
	// char	*executable;

	// executable = *ptr_executable;
	// if (executable[0] == '/')
	// {
	// 	ft_printf("Absolute path\n");
	// 	// return ;
	// 	// Just return
	// }
	// else if (!ft_strncmp(executable, "./", 2))
	// {
	// 	// ft_memmove(executable, executable + 1, ft_strlen(executable + 1) + 1);
	// 	// executable = ft_strmodify(executable, getenv("PWD"), ft_strrjoin);
	// 	ft_printf("Current path\n");
	// }
	// else if (ft_strchr(executable, '/'))
	// {
	// 	// executable = ft_strcombine(ft_strjoin(getenv("PWD"), "/"), executable);
	// 	ft_printf("Relative path\n");
	// }
	// else
	// {
	// 	ms_pathaccess(&executable);
	// 	ft_printf("PATHVAR\n");
	// }
	// *ptr_executable = executable;
	// ft_printf("PathJoined: %s\n", executable);
// }
