/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:54:58 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/01/27 15:21:14 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include <stdbool.h>
# include "libft.h"

typedef enum
{
	TOKEN_COMMAND,
	TOKEN_ARGUMENT,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_HEREDOC,
	TOKEN_APPEND,
	TOKEN_SPECIAL_CHAR,
	TOKEN_UNKNOWN,
}	t_token_type;

typedef struct	s_token
{
	char			*value;
	t_token_type	type;
}	t_token;

char	*ms_strtok(char *str, char *delimiter);
char	**ms_tokens_arr_create(char *input);
void	ms_tokens_arr_free(char ***tokens_arr);
#endif