/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:54:58 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/01/03 18:27:24 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include <stdbool.h>
# include "libft.h"

char	*ms_strtok(char *str, char *delimiter);
char	**ms_tokens_arr_create(char *input);
void	ms_tokens_arr_free(char ***tokens_arr);
#endif