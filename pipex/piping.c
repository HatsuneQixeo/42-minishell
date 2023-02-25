/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 08:01:14 by hqixeo            #+#    #+#             */
/*   Updated: 2023/02/25 10:21:05 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

/**
 * @brief Exclude argv from absolute path
 * 
 * @param cmd 
 * @param envp 
 */
void	ft_execve(const char *cmd, char **envp)
{
	char	**command;

	command = ft_split(cmd, ' ');
	ft_pathaccess(envp, command);
	execve(*command, command, envp);
	ft_dprintf(2, "zsh: command not found: %s\n", *command);
	exit(127);
}

int	ft_exec(const char *cmd, char **envp)
{
	return (ft_exec_fd(cmd, envp, 0, 1));
}

/// @note This function does not allow concurrent action
int	ft_exec_fd(const char *cmd, char **envp, int fd_in, int fd_out)
{
	pid_t	child;
	int		status;

	status = 0;
	child = fork();
	if (child == -1)
		ft_errexit(EXIT_FAILURE, "fork");
	else if (child == 0)
	{
		ft_dup3(fd_in, STDIN_FILENO);
		ft_dup3(fd_out, STDOUT_FILENO);
		ft_execve(cmd, envp);
	}
	else
		waitpid(child, &status, 0);
	return (WEXITSTATUS(status));
}

static void	pipex_pipeloop(int argc, char **argv, char **envp, int *pipex)
{
	int	i;
	int	prev_read;

	i = 2;// + first command + infile
	while (++i < argc - 2)// - lastcommand - outfile
	{
		prev_read = pipex[READ_END];
		ft_pipeinit(pipex);
		ft_exec_fd(argv[i], envp, prev_read, pipex[WRITE_END]);
		close(prev_read);
		close(pipex[WRITE_END]);
	}
}

void	pipex_core(int argc, char **argv, char **envp, int out_option)
{
	int	pipex[2];
	int	fd_infile;
	int	fd_outfile;

	fd_outfile = ft_getfd(argv[argc - 1], out_option, 0644);
	fd_infile = ft_getfd(argv[1], O_RDONLY, 0);
	ft_pipeinit(pipex);
	ft_exec_fd(argv[2], envp, fd_infile, pipex[WRITE_END]);
	close(fd_infile);
	close(pipex[WRITE_END]);
	pipex_pipeloop(argc, argv, envp, pipex);
	ft_exec_fd(argv[argc - 2], envp, pipex[READ_END], fd_outfile);
	close(fd_outfile);
	close(pipex[READ_END]);
}
