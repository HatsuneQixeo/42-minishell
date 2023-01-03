/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 16:55:23 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/01/03 15:14:51 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "lexer.h"

void    ms_lexer(char *input)
{
	char	**tokens_arr;

	tokens_arr = ms_tokens_arr_create(input);
	int i = -1;
	while (tokens_arr[++i])
		printf("%s\n", tokens_arr[i]);
	// ms_tokens_arr_free(&tokens_arr);
}