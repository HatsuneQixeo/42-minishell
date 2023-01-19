/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 08:01:22 by hqixeo            #+#    #+#             */
/*   Updated: 2022/11/13 08:01:25 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"

# define READ_END	0
# define WRITE_END	1
// here_doc
void	pipex_here_doc(int argc, char **argv, char **envp);
// Utils
void	ft_pipeinit(int *pipex);
void	ft_dup3(int fd, int fd_new);
int		ft_getfd(const char *path, int option, int creat_permission);
void	ft_errexit(int exitstatus, const char *errorname);

// Piping
int		ft_exec(const char *cmd, char **envp);
int		ft_exec_fd(const char *cmd, char **envp, int fd_in, int fd_out);
void	pipex_core(int argc, char **argv, char **envp, int out_option);

// Path and envp
char	*ft_findenvp(char **envp, const char *varname);
void	ft_pathaccess(char **envp, char **command);
#endif
