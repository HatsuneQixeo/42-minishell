/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:21:07 by hqixeo            #+#    #+#             */
/*   Updated: 2023/02/25 18:26:23 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

t_token	*token_new(char *str, enum e_tokentype type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->value = str;
	token->type = type;
	return (token);
}

void	del_token(void *content)
{
	t_token	*token;

	token = content;
	free(token->value);
	free(token);
}

const char	*lstname_token(const char *newname)
{
	static const char	*name = "token";

	if (newname != NULL)
		name = newname;
	return (name);
}

void	show_token(int i, void *content)
{
	const t_token	*token = content;
	const char		*str_type;

	if (token->type == RDRT)
		str_type = CYAN"Redirect";
	else if (token->type == CTRL)
		str_type = YELLOW"Control";
	else if (token->type == SUBSH_BEGIN || token->type == SUBSH_END)
		str_type = MAGENTA"Subshell";
	else
		str_type = GREY"Default";
	ft_dprintf(2, "%s[%2d]: %-8s: %b\n"DEF,
		lstname_token(NULL), i, str_type, token->value);
}
