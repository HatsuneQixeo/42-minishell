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

int	ms_isbuiltin(const char *command_expanded, t_data *data);

/**
 * @brief return (-!!ft_dprintf(2, MINISHELL": %s: %s\n", name, error));
 * @return int -1
 */
int	ms_errorlog(const char *name, const char *error)
{
	return (-!!ft_dprintf(2, MINISHELL": %s: %s\n", name, error));
}

t_list	*parser_ctrl(t_list **lst_token);
t_list	*parser_recursive(t_list **lst_token);

void	ms_procedure(t_data *data, const char *raw)
{
	char	*input;

	input = ms_closequote(raw);
	if (input == NULL)
		return ;
	add_history(input);
	t_list	*lst = ms_lexer(input);
	free(input);

	lstiter_tokenname("lexed");
	ft_lstiter(lst, lstiter_showtoken);
	/* Return if syntax error */
	if (parser_syntax(lst) == -1)
	{
		ft_lstclear(&lst, del_token);
		return ;
	}
	/**
	 * @brief Parser
	 * Build the syntax tree
	 * 	Interpreter will handle file not found and ambiguous shenanigan
	 * 		But syntax error still need to be checked
	 */
	// t_list	*lst_ctrl = parser_ctrl(&lst);
	t_list	*lst_ctrl = parser_recursive(&lst);

	show_ctrl(lst_ctrl);
	// parser_subshell(&lst_ctrl);
	ft_lstclear(&lst_ctrl, del_ctrl);
	if (lst != NULL)
	{
		lstiter_tokenname("leftover");
		ft_lstiter(lst, lstiter_showtoken);
		ft_lstclear(&lst, del_token);
	}
	return ;
	/**
	 * Intepretor
	 * Lexer? and expander Should be inside interpretor because ambiguous is error during execution
	 * if lexer is in intepretor, how can parser check for error?
	 * 	takes in a list of tokens, set up | first? and then do the redirection ><
	*/
	/**
	 * @brief Lexer also in interpretor
	 * 	Turn the DEFAULT into argv?
	 * 
	 */
	/**
	 * @brief Expander in interpretor
	 * Probably should do this in executor because of ambiguous redirect?
	 * Ambiguous is a execution time error so
	 * Need to expand the given argv first before parser
	 * 	Because echo $MIKU > $MIKU would result in Hatsune Miku Miku in a Hatsune file
	 * (Oh wait, Ambiguous redirect if the expanded variable contain space and not quoted)
	 * Ambiguous also only happen in execution so
	 * 
	 */
}

void	ms_input(char **src_envp)
{
	t_data	data;
	char	*input;

	data.envp = ft_strlistdup(src_envp);
	input = readline(MINISHELL"$ ");
	while (input != NULL)
	{
		if (*input != '\0')
			ms_procedure(&data, input);
		free(input);
		input = readline(MINISHELL"$ ");
	}
	ft_strlistclear(data.envp);
}
