/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 12:18:39 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/01/09 03:13:28 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ms_lexer(const char *src);

void	ms_execve(const char *cmd, char **envp)
{
	char	**command;

	command = ms_lexer(cmd);
	ft_pathaccess(envp, command);
	execve(*command, command, envp);
	ft_dprintf(2, "zsh: command not found: %s\n", *command);
	exit(127);
}

void	ft_lstappend(t_list **lst, void *content)
{
	ft_lstadd_back(lst, ft_lstnew(content));
}

char	*ms_expander(const char *command_line);
void	ms_command_line(char **envp, const char *command_line)
{
	char	*parsed;
	char	*expanded;
	char	*lexed;

	/// @note Parser goes first, checking for syntax error, setting up the pipe and stuff too I assume
	// parsed = 
	if (parsed == NULL)
		return ;
	(void)parsed;
	(void)lexed;
	/// @note Expander goes after for bash
	/// @note Expand $MIKU to Hatsune Miku, $HOME to /Users/$INTRANAME etc..
	expanded = ms_expander(command_line);
	/// @note Show the result of ms_expander
	ft_printf("expanded[ %s ]\n", command_line, expanded);


	/// @note Lexer
	// data.prg_argv = ms_lexer(command_line);
	// ft_strlistclear(data.prg_argv);

	/// @note Execution
	// ms_executablepath(envp, )
	// if (expanded == NULL)
	// 	ft_printf("NULLEXPAND of raw: %s\n", command_line);
	// else
		// g_last_exitstatus = ft_exec(expanded, data.envp);
	/// @note Lets modify this function to take in argv instead?
	g_last_exitstatus = ft_exec(expanded, envp);
	free(expanded);
}

void	ms_input(char **envp)
{
	char	*input;

	input = readline(MINISHELL);
	while (input != NULL)
	{
		// Add the input to history
		if (*input != '\0')
		{
			add_history(input);
			// Process and execute the given command line
			ms_command_line(envp, input);
		}
		free(input);
		input = readline(MINISHELL);
	}
}
