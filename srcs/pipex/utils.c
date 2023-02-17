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
void	ms_perror(const char *name);

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
	if (fd == fd_new || fd == -1 || fd_new == -1)
		return ;
	if (dup2(fd, fd_new) == -1)
	{
		ft_dprintf(2, "zsh: %s: %s\n", strerror(errno), "dup2");
		ft_dprintf(2, "fd: %d\nfd_new: %d\n", fd, fd_new);
	}
	if (close(fd) == -1)
		ft_dprintf(2, "close error (fd: %d)\n", fd);
}

int	ft_getfd(const char *path, int option, ...)
{
	int		fd;
	va_list	args;

	if (option & O_CREAT)
	{
		va_start(args, option);
		fd = open(path, option, va_arg(args, int));
	}
	else
		fd = open(path, option);
	if (fd == -1)
		ms_perror(path);
	va_end(args);
	return (fd);
}
