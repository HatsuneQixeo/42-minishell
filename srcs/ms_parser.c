/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 12:16:10 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/01/09 03:20:31 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parser_quoteend(const char *src)
{
	char	*end;
	char	quote;

	quote = src[0];
	end = ft_strchr(&src[1], quote);
	if (end != NULL)
		return (end);
	ft_dprintf(2, "Error: Missing Closing end: (%c) at (%s)\n", quote, src);
	return (end);
	/// @note Let's not think about this for now 
	// char	*buffer;

	// buffer = ft_strdup(src);
	// while (end == NULL || end[-1] == '\\')
	// {
	// 	buffer = ft_strjoin(buffer, readline("> "));
	// 	end = ft_strchr(&buffer[1], buffer[0]);
	// }
	// return (buffer);
}

int	ft_open(const char *path, int option, int creat_permission)
{
	int	fd;

	fd = open(path, option, creat_permission);
	if (fd == -1)
		perror(path);
	return (fd);
}

typedef struct s_process
{
	int		fd_in;
	int		fd_out;
	char	*command;
	struct s_process	*doif_success;
	struct s_process	*doif_failure;
}			t_process;

/// @brief Will just detect missing closing end for now?
/// @note Gonna have to recognize << < > >> | (bonus)(&& || *)
/// @param command_line 
/// @return 
/// @note '|', '&&', '||' Should have their own individual process and command to execute
/// @note '&&' Should Have it's own parsed command, the delimiter shall be another '&&' or '||'

int	ft_exitsuccess(void)
{
	return (g_last_exitstatus == 0);
}

int	ft_exitfailure(void)
{
	return (g_last_exitstatus != 0);
}

char	*ms_parser(const char *command_line)
{
	char	*it;

	it = (char *)&command_line[-1];
	while (*++it != '\0')
	{
		if (*it == '\'' || *it == '\"')
		{
			it = parser_quoteend(it);
			if (it == NULL)
				return (NULL);
		}
		else if (*it == '|')
		{
			ft_printf("pipe\n");
		}
		else if (*it == '<')
		{
			if (*(it + 1) == '<')
				ft_printf("heredoc\n");
			ft_printf("Pipe the content of the given file into the stdin\n"
				"Have higher priority over '|' character\n"
				"Or it's' just that the '<' is evaluated after '|'\n"
				"ex: cat < a | ls | cat < b\n");
		}
		else if (*it == '>')
		{
			if (*(it + 1) == '>')
				ft_printf("Redirect stdout and append to the given file\n");
			else
				ft_printf("Redirect stdout to the given file\n");
		}
		else if (*it == '*')
		{
			ft_printf("Wildcard substitution\n");
		}
		else if (!ft_strncmp(it, "&&", 2) && g_last_exitstatus == 0)
		{
			ft_printf("Execute the next command if this expression result in success\n");
		}
		else if (!ft_strncmp(it, "||", 2) && g_last_exitstatus != 0)
		{
			ft_printf("Execute the next command if this expression result in error\n");
		}
	}
	return (NULL);
}
