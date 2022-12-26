/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 17:31:06 by ntan-wan          #+#    #+#             */
/*   Updated: 2022/12/26 17:41:09 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H
# define MAX_TOKEN_LEN 100

# include "../libft/libft.h"
# include <stdio.h>
# include <stdbool.h>

typedef enum e_token_type
{
	COMMAND,
	ARGUMENT,
	REDIRECTION,
	PIPE,
	UNKNOWN
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			value[MAX_TOKEN_LEN];
	struct s_token	*next;
}	t_token;

void	ms_tokenize(char *input);
#endif