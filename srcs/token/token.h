/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:21:08 by hqixeo            #+#    #+#             */
/*   Updated: 2023/02/27 16:12:50 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "ms_common.h"

enum e_tokentype
{
	DEFAULT,
	RDRT,
	CTRL,
	SUBSH_BEGIN,
	SUBSH_END,
	TOKENCOUNT
};

typedef struct s_token
{
	enum e_tokentype	type;
	char				*value;
}			t_token;

t_token		*token_new(char *str, enum e_tokentype type);
void		del_token(void *content);
const char	*lstname_token(const char *newname);
void		lstshow_token(void *content);

#endif
