/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:15:54 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/18 14:28:14 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
	@brief One of the way to traverse binary tree.
	@note This method is called inorder traversal.
	@note The other 2 ways to traverse are: preorder traversal
	and postorder traversal.
 */
void	traverse_tree_inorder(t_ast *root, int (*f)(t_ast *))
{
	if (!root)
		return ;
	traverse_tree_inorder(root->left, f);
	f(root);
	traverse_tree_inorder(root->right, f);
}

/* 
	@brief Check whether the file is executable.
	@note Print error msg accordingly if error is encountered.
 */
bool	is_executable(char *path_to_file)
{
	struct stat	file_stat;

	ft_bzero(&file_stat, sizeof(struct stat));
	if (stat(path_to_file, &file_stat) == -1)
	{
		util_perror(path_to_file, ": command not found");
		return (false);
	}
	else if ((file_stat.st_mode & S_IFMT) == S_IFDIR)
	{
		util_perror(path_to_file, ": Is a directory");
		return (false);
	}
	else if ((file_stat.st_mode & S_IFMT) == S_IFREG)
	{
		if ((file_stat.st_mode & S_IXUSR) == 0)
		{
			util_perror(path_to_file, ": Permission denied");
			return (false);
		}
	}
	return (true);
}

/* 
	@brief Execute heredoc first, then execute the rest.
 */
void	ms_executor(t_ast *root)
{
	traverse_tree_inorder(root, execute_heredoc);
	execute_cmdline(root);
}
