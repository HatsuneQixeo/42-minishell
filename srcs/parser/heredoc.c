/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:21:06 by hqixeo            #+#    #+#             */
/*   Updated: 2023/02/25 10:21:06 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_common.h"

/* Return 0 is given limiter has no quote, 1 if has quote */
int	heredoc_limiter(char *limiter)
{
	int	hasquote;

	hasquote = 0;
	while (*limiter != '\0')
	{
		if (!ft_isquote(*limiter))
		{
			limiter++;
			continue ;
		}
		ft_memmove(limiter, limiter + 1, ft_strlen(limiter + 1) + 1);
		hasquote = 1;
	}
	return (hasquote);
}

t_list	*heredoc(const char *limiter)
{
	t_list	*lst_buffer;
	char	*input;

	lst_buffer = NULL;
	while (1)
	{
		input = readline("heredoc> ");
		if (input == NULL || !ft_strcmp(limiter, input))
			break ;
		ft_lstadd_back(&lst_buffer, ft_lstnew(input));
	}
	free(input);
	return (lst_buffer);
}
