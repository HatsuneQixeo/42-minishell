/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:14:42 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/02/20 23:48:05 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **envp)
{
	char			*input;
	t_double_list	*token_list;
	
	input = NULL;
	token_list = NULL;
	util_clear_screen();
	while (true)
	{
		input = readline("🐚 $ ");
		if (input && ft_strncmp(input, "exit", 4))
		{
			add_history(input);
			token_list = ms_tokenizer(input);
			ms_parser(token_list);
			//
			debug_token_list_content_print(token_list);
			//
			free(input);
			token_list_free(&token_list);
		}
		else
			break ;
	}
	free(input);
	token_list_free(&token_list);
}