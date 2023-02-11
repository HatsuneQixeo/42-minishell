/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:16:22 by ntan-wan          #+#    #+#             */
/*   Updated: 2022/10/20 11:07:12 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
	stdio.h is included as BUFSIZ is declared in here.
	The value for BUFSIZ should normally be 256KB, 512 KB or 4096 KB. This 
	depends on the system and the compiler.
*/

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE BUFSIZ
# endif

char	*get_before_newline(const char *str);
char	*get_after_newline(const char *str);
char	*parse_line(char **storage, char **temp);
void	read_from_fd(int fd, char **storage, char **temp);
char	*get_next_line(int fd);

/* utils */
char	*t_strdup(const char *str1);
void	*malloc_zero(size_t count, size_t size);
void	free_strs(char **str1, char **str2, char **str3);
char	*join_strs(const char *str1, const char *str2);
int		contain_newline(const char *str);
#endif