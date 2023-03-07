/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:22:17 by hqixeo            #+#    #+#             */
/*   Updated: 2023/03/07 15:22:17 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rdrt.h"

/**
 * @brief Closes the original fd, essentially function as replacing the fd.
 * @note Does not do anything if the fd_attribute is the same as ft_value
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
	else if (fd_attribute == -1)
		ft_dprintf(2, "fd_attribute: %d\n", fd_attribute);
	else if (fd_value == -1)
		ft_dprintf(2, "fd_value: %d\n", fd_value);
	else if (dup2(fd_attribute, fd_value) == -1)
	{
		ms_perror("dup2");
		ft_dprintf(2, "fd_attribute: %d\n", fd_attribute);
		ft_dprintf(2, "fd_value: %d\n", fd_value);
	}
	else if (close(fd_attribute) == -1)
		ft_dprintf(2, "close error (fd_attribute: %d)\n", fd_attribute);
	else
		return (0);
	return (-1);
}
