/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parens_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 18:51:27 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/01/02 17:28:57 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

/* 
	Ignore the chars inside the quote by iterate through
	the chars until it reach the next quote.	
 */
static void	handle_quote(char *str, int *i)
{
	char	quote;

	if (str[*i] == '\'' || str[*i] == '\"')
	{
		quote = str[(*i)++];
		while (str[++(*i)] && str[*i] != quote)
		++(*i);
	}
}

static bool	is_pair_parens(char c1, char c2)
{
	return (c1 == '(' && c2 == ')');
}

bool	is_balanced_parens(char *str)
{
	int		i;
	int		top;
	t_stack	*stack;

	i = -1;
	stack = stack_create(ft_strlen(str));
	while (str[++i])
	{
		handle_quote(str, &i);
		if (str[i] == '(')
			stack_push(stack, str[i]);
		else if (str[i] == ')')
		{
			if (is_pair_parens(stack->arr[stack->top], str[i]))
				stack_pop(stack);
			else
			{
				stack_free(&stack);
				return (false);
			}
		}
	}
	top = stack->top;
	stack_free(&stack);
	return (top == -1);
}
