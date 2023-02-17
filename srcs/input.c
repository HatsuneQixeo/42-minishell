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
# include "builtin.h"

char	*ms_parser(t_data *data, const char *command_line);

int	ms_isbuiltin(const char *command_expanded, t_data *data);
t_list	*ms_tokenizer(const char *src);

/**
 * @brief return (-!!ft_dprintf(2, MINISHELL": %s: %s\n", name, error));
 * @return int -1
 */
int	ms_errorlog(const char *name, const char *error)
{
	return (-!!ft_dprintf(2, MINISHELL": %s: %s\n", name, error));
}

void	parser_rdrt(t_list **lst_token);
t_list	*parser_ctrl(t_list **lst_token);

void	ms_procedure(t_data *data, const char *raw)
{
	char	*input;

	input = ms_closequote(raw);
	if (input == NULL)
		return ;
	add_history(input);
	input = ft_strmodify(ft_strtrim, input, "\t \n");
	t_list	*lst = ms_lexer(input);
	free(input);

	lstiter_tokenname("lexed");
	ft_lstiter(lst, lstiter_showtoken);
	if (parser_syntax(lst) == -1)
	{
	}
	ft_lstclear(&lst, del_token);
	return ;
	// parser_rdrt(&lst);
	// parser_ctrl(&lst);
	/**
	 * @brief Expander ?!
	 * Probably should do this in executor because of ambiguous redirect?
	 * Ambiguous is a execution time error so
	 * Need to expand the given argv first before parser
	 * 	Because echo $MIKU > $MIKU would result in Hatsune Miku Miku in a Hatsune file
	 * (Oh wait, Ambiguous redirect if the expanded variable contain space and not quoted)
	 * Ambiguous also only happen in execution so
	 * 
	 */
	/**
	 * @brief Parser
	 * 	Check for syntax error
	 * 	Check for missing argument for operator
	 * Build the syntax tree
	 * 	Interpreter will handle file not found and ambiguous shenanigan
	 * 		But syntax error still need to be checked
	 * Interpreter should take in a list of token like >> > < << |, but not && ||
	 *	When? Should I let the intepreter handle everything else other than parsing argv?
	 */
	/**
	 * @brief Expander ?!
	 * Maybe I should do the expansion in parser?
	 * Expand the value after comfirming the syntax
	 * BUT > $UNDEFINED_VARIABLE/$UNQUOTE_WITH_SPACE also result in Ambiguous
	 * 	Only for DEFAULT token type
	 * 
	 * @note Maybe I can expand the value after tokenizer,
	 * 	Special character should not be interpreted as such with token attribute
	 */

	/**
	 * @brief Lexer
	 * 	Turn the DEFAULT into argv?
	 * 
	 */
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
	input = readline(MINISHELL"$ ");
	while (input != NULL)
	{
		// Add history, process and execute the given command line
		if (*input != '\0')
			// ms_command_line(&data, input);
			ms_procedure(&data, input);
		free(input);
		input = readline(MINISHELL"$ ");
	}
	ft_strlistclear(data.envp);
}
