/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_btree.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 13:41:28 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/02/10 14:03:02 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_BTREE_H
# define MS_BTREE_H

typedef struct	s_node
{
	void			*content;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

#endif