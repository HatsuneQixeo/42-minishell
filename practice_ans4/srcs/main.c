/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:14:42 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/02/12 00:02:51 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"


int main()
{
    t_double_list  *list;

    list = ms_tokenizer("hello world >>testin");
    ms_token_list_concat_same_type(&list);
    debug_token_list_content_print(list);
    ms_token_list_free(&list);
}