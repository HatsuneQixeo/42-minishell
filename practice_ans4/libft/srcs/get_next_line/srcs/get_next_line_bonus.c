/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 14:12:06 by ntan-wan          #+#    #+#             */
/*   Updated: 2022/10/20 11:07:12 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_before_newline(const char *str)
{
	char	*result;
	int		i;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] != '\0' && str[i] == '\n')
		i++;
	result = malloc_zero(i + 1, sizeof(result));
	if (!result)
		return (NULL);
	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
	{
		result[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		result[i] = str[i];
		i++;
	}
	return (result);
}

char	*get_after_newline(const char *str)
{
	char	*result;
	int		i;
	int		j;

	j = 0;
	while (str && str[j])
		j++;
	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] != '\0' && str[i] == '\n')
		i++;
	result = malloc_zero((j - i) + 1, sizeof(result));
	if (!result)
		return (NULL);
	j = 0;
	while (str[i + j])
	{
		result[j] = str[i + j];
		j++;
	}
	return (result);
}

void	read_from_fd(int fd, char **storage, char **temp)
{
	char	*buffer;
	int		r;

	buffer = malloc(sizeof(buffer) * (BUFFER_SIZE + 1));
	if (!buffer)
		return ;
	r = 1;
	while (r > 0)
	{
		r = read(fd, buffer, BUFFER_SIZE);
		if (r == -1)
		{
			free_strs(&buffer, storage, temp);
			return ;
		}
		buffer[r] = '\0';
		*temp = t_strdup(*storage);
		free_strs(storage, 0, 0);
		*storage = join_strs(*temp, buffer);
		free_strs(temp, 0, 0);
		if (contain_newline(*storage))
			break ;
	}
	free_strs(&buffer, 0, 0);
}

char	*parse_line(char **storage, char **temp)
{
	char	*line;

	*temp = t_strdup(*storage);
	free_strs(storage, 0, 0);
	*storage = get_after_newline(*temp);
	line = get_before_newline(*temp);
	free_strs(temp, 0, 0);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*storage[1024];
	char		*temp;
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd >= 1024)
		return (NULL);
	temp = NULL;
	line = NULL;
	read_from_fd(fd, &storage[fd], &temp);
	if (storage[fd] != NULL && *storage[fd] != '\0')
		line = parse_line(&storage[fd], &temp);
	if (!line || *line == '\0')
	{
		free_strs(&storage[fd], &line, &temp);
		return (NULL);
	}
	return (line);
}
