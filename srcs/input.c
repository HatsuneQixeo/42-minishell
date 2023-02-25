/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 12:18:39 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/02/25 10:21:06 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_procedure(t_data *data, const char *raw)
{
	char	*input;

	input = ms_closequote(raw);
	if (input == NULL)
		return ;
	add_history(input);
	t_list	*lst = ms_lexer(input);
	free(input);

	if (parser_syntax(lst) == -1)
	{
		ft_lstclear(&lst, del_token);
		return ;
	}
	t_list	*lst_ctrl = ms_parser(&lst);

	// show_lstctrl(lst_ctrl);
	ms_interpretor(data, &lst_ctrl);
	leakcheck("interpretor end");
}

void	ms_input(char **src_envp)
{
	t_data	data;
	char	*input;

	data.fd_std[0] = dup(0);
	data.fd_std[1] = dup(1);
	data.envp = ft_strlistdup(src_envp);
	while (1)
	{
		input = readline(MINISHELL"$ ");
		if (input == NULL)
			break ;
		else if (*input != '\0')
			ms_procedure(&data, input);
		free(input);
	}
	close(data.fd_std[0]);
	close(data.fd_std[1]);
	ft_strlistclear(data.envp);
}
