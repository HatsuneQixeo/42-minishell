/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_stack_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 09:25:40 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/02/22 23:57:22 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_stack	*stack_create(int max)
{
	int		i;
	t_stack	*new_stack;

	new_stack = malloc(sizeof(t_stack));
	new_stack->top = -1;
	new_stack->max_size = max;
	new_stack->arr = ft_calloc(max + 1, sizeof(char));
	return (new_stack);
}

bool	stack_is_full(t_stack *stack)
{
	return (stack->top == stack->max_size - 1);
}

bool	stack_is_empty(t_stack *stack)
{
	return (stack->top == -1);
}

void	stack_push(t_stack *stack, char item)
{
	if (stack_is_full(stack))
		return ;
	stack->arr[++stack->top] = item;
}

void	stack_pop(t_stack *stack)
{
	if (stack_is_empty(stack))
		return ;
	stack->arr[stack->top] = '\0';
	stack->top--;
}
