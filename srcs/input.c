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
	/**
	 * @brief Parser
	 * Build the syntax tree
	 * Interpreter will handle file not found and ambiguous shenanigan
	 * 	But syntax error still need to be checked
	 */
	/**
	 * @brief Heredoc
	 * Let's do it here, before the syntax tree is built
	 * I dunno, maybe I would need to split the syntax builder later or sooner?
	 * Let's wait until then?
	 * 
	 */
	t_list	*lst_ctrl = ms_parser(data->envp, &lst);

	// show_lstctrl(lst_ctrl);
	if (lst != NULL)
	{
		debuglst_tmpname(lst, lstiter_tokenname, "leftover", lstiter_showtoken);
		ft_lstclear(&lst, del_token);
	}
	ms_interpretor(data->envp, &lst_ctrl);
	if (lst_ctrl != NULL)
	{
		ft_printf("LEFTOVER AFTER EXECUTION\n");
		show_lstctrl(lst_ctrl);
		ft_lstclear(&lst_ctrl, del_ctrl);
	}
	return ;
	/**
	 * Intepretor
	 * Lexer? and expander Should be inside interpretor because ambiguous is error during execution
	 * if lexer is in intepretor, how can parser check for error?
	 * 	takes in a list of tokens, set up | first? and then do the redirection ><
	*/
}

void	ms_input(char **src_envp)
{
	t_data	data;
	char	*input;

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
	ft_strlistclear(data.envp);
}
