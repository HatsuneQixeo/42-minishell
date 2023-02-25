/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 08:01:19 by hqixeo            #+#    #+#             */
/*   Updated: 2023/02/25 10:21:05 by hqixeo           ###   ########.fr       */
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

/**
 * @brief Closes the original fd, essentially function as replacing the fd
 * 
 * @param fd_attribute The attribute of the file descriptor
 * @param fd_value The value of the file descriptor
 * 
 * @return int -1 if either fd is -1, or either dup2 or close failed,
 * 	0 by default
 */
int	ft_dup3(int fd_attribute, int fd_value)
{
	if (fd_attribute == fd_value)
		return (0);
	else if (fd_attribute == -1 || fd_value == -1)
		return (-1);
	else if (dup2(fd_attribute, fd_value) == -1)
	{
		ft_dprintf(2, "zsh: %s: %s\n", strerror(errno), "dup2");
		ft_dprintf(2, "fd_attribute: %d\n", fd_attribute);
		ft_dprintf(2, "fd_value: %d\n", fd_value);
	}
	else if (close(fd_attribute) == -1)
		ft_dprintf(2, "close error (fd_attribute: %d)\n", fd_attribute);
	else
		return (0);
	return (-1);
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
