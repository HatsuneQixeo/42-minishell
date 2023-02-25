/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:21:08 by hqixeo            #+#    #+#             */
/*   Updated: 2023/02/25 18:26:23 by hqixeo           ###   ########.fr       */
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

/* Isoperator */
int			isoperator_ctrl(enum e_tokentype type);
int			isoperator_rdrt(enum e_tokentype type);
int			isoperator_subsh(enum e_tokentype type);

/* Token */
t_token		*token_new(char *str, enum e_tokentype type);
void		del_token(void *content);
const char	*lstname_token(const char *newname);
void		lstshow_token(int i, void *content);

#endif
