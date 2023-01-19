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

void	ft_lstappend(t_list **lst, void *content)
{
	ft_lstadd_back(lst, ft_lstnew(content));
}

t_data	ms_data_init(char **envp)
{
	t_data	data;

	data.input_raw = NULL;
	data.input_expanded = NULL;
	data.prg_argv = NULL;
	data.envp = envp;
	return (data);
}

char	*ms_expander(const char *command_line);
void	ms_command_line(t_data data, const char *command_line)
{
		// Expand $MIKU to Hatsune Miku, $HOME to /Users/$INTRANAME etc..
		data.input_expanded = ms_expander(command_line);
		// Show the result of ms_expander
		ft_printf("%s >> %s\n", data.input_raw, data.input_expanded);

		// Parsing goes here after expander for bash
		data.prg_argv = ms_lexer(data.input_raw);
		ft_strlistclear(data.prg_argv);
		// Syntax checking before execution, probably need to handle missing closing end
		//	(Maybe backslash end too?)

		// Execution
		// ms_executablepath(envp, )
		if (data.input_expanded == NULL)
			ft_printf("NULLEXPAND of raw: %s\n", data.input_raw);
		else
			g_last_exitstatus = ft_exec(data.input_expanded, data.envp);
		free(data.input_expanded);
}

void	ms_input(char **envp)
{
	t_data	data;

	data = ms_data_init(envp);
	data.input_raw = readline("🐚 $ ");
	while (data.input_raw != NULL)
	{
		// Add the input to history
		add_history(data.input_raw);
		// Process and execute the given command line
		ms_command_line(data, data.input_raw);
		free(data.input_raw);
		// ft_strlistclear(data.prg_argv);
		data.input_raw = readline("🐚 $ ");
	}
}
