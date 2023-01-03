/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 08:09:24 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/01/03 14:08:27 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_H
# define NODE_H

# include <stdlib.h>
# include "../libft/libft.h"

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_VAR
}	t_node_type;

typedef enum e_val_type
{
	VAL_SINT = 1,
	VAL_UINT,
	VAL_SLLONG,
	VAL_ULLONG,
	VAL_FLOAT,
	VAL_LDOUBLE,
	VAL_CHAR,
	VAL_STR
}	t_val_type;

typedef union u_symval
{
	char				c;
	char				*str;
	long				sint;
	unsigned long		uint;
	long long			sllong;
	unsigned long long	ullong;
	double				sfloat;
	long double			ldouble;
}	t_symval;

typedef struct s_node
{
	t_node_type		type;
	t_symval		val;
	t_val_type		val_type;
	int				childs_count;
	struct s_node	*first_child;
	struct s_node	*prev_sibling;
	struct s_node	*next_sibling;
}	t_node;

void    free_node_tree(t_node *node);
t_node	*node_init(t_node_type type);
void    set_node_val_str(t_node *node, char *val);
void    add_child_node(t_node *parent, t_node *child);
#endif