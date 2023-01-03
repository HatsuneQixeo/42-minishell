/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 09:33:38 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/01/03 18:27:00 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H

# include <stdlib.h>
# include <stdbool.h>
# include "libft.h"

typedef struct s_stack
{
	int		top;
	char	*arr;
	int		max_size;
}	t_stack;

t_stack	*stack_create(int max);
void	stack_pop(t_stack *stack);
void	stack_free(t_stack **stack);
bool	stack_is_full(t_stack *stack);
bool	stack_is_empty(t_stack *stack);
void	stack_push(t_stack *stack, char item);
#endif