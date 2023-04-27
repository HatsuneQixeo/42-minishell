/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 12:10:40 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/16 02:21:41 by hqixeo           ###   ########.fr       */
/*                                                                           */
/* ************************************************************************** */
#include "ms_common.h"
#include "rdrt.h"

void	minishell(t_data *data);

int	read_script(const char *path)
{
	const int	fd = open(path, O_RDONLY);

	if (fd == -1)
		perror(path);
	else if (ft_dup3(fd, 0) != -1)
		return (0);
	return (1);
}

/*
	To make the shell script actually support $1 $2,
	I probably have to pass argc and argv around

	Nah, know enough about this already, let's move on
*/
int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	data = (t_data){
		.argc = argc,
		.argv = (const char **)argv,
		.envp = ft_strlistdup(envp),
		.isscript = argc != 1,
	};
	if (data.isscript && read_script(argv[1]) == -1)
		return (1);
	minishell(&data);
}
