/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 08:01:19 by hqixeo            #+#    #+#             */
/*   Updated: 2022/11/13 08:01:20 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_errexit(int exitstatus, const char *errorname)
{
	// ft_dprintf(2, "zsh: %s: %s\n", strerror(errno), errorname);
	ft_dprintf(2, "bash: ");
	perror(errorname);
	exit(exitstatus);
}

void	ft_pipeinit(int *pipex)
{
	if (pipe(pipex) == -1)
		ft_errexit(EXIT_FAILURE, "pipefailed");
}

//Closes the original fd, essentially function as replacing the fd
void	ft_dup3(int fd, int fd_new)
{
	if (fd == fd_new)
		return ;
	if (dup2(fd, fd_new) == -1)
	{
		ft_dprintf(2, "zsh: %s: %s\n", strerror(errno), "dup2");
		ft_dprintf(2, "fd: %d\nfd_new: %d\n", fd, fd_new);
	}
	if (close(fd) == -1)
		ft_dprintf(2, "close error (fd: %d)\n", fd);
}

int	ft_getfd(const char *path, int option, int creat_permission)
{
	int	fd;

	fd = open(path, option, creat_permission);
	if (fd == -1)
		ft_errexit(EXIT_FAILURE, path);
	return (fd);
}
