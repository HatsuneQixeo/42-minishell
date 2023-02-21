// #include "minishell.h"

// static void	rdrt_error(t_token *token, const char *type)
// {
// 	ft_dprintf(2, "rdrt_%s receiving incorrect token: %s\n", type, token->type);
// }

// static int	rdrt_core(const char *path, int std_fileno, int option, ...)
// {
// 	int		fd;
// 	va_list	args;

// 	va_start(args, option);
// 	fd = open(path, option, va_arg(args, int));
// 	va_end(args);
// 	if (fd == -1)
// 	{
// 		ms_perror(path);
// 		return (-1);
// 	}
// 	ft_dup3(fd, std_fileno);
// 	return (0);
// }

// int	rdrt_heredoc(t_token *token)
// {
// 	if (token->type != RDRT_HEREDOC)
// 		rdrt_error(token, "heredoc");
// 	else
// 		return (rdrt_core(HEREDOCTXT, STDIN_FILENO, O_RDONLY));
// 	return (-1);
// }

// int	rdrt_append(t_token *token)
// {
// 	if (token->type != RDRT_APPEND)
// 		rdrt_error(token, "append");
// 	else
// 		return (rdrt_core(token->value, STDOUT_FILENO,
// 			O_CREAT | O_APPEND | O_WRONLY, 0644));
// 	return (-1);
// }

// int	rdrt_input(t_token *token)
// {
// 	if (token->type != RDRT_INPUT)
// 		rdrt_error(token, "input");
// 	else
// 		return (rdrt_core(token->value, STDIN_FILENO, O_RDONLY));
// 	return (-1);
// }

// int	rdrt_overwrite(t_token *token)
// {
// 	if (token->type != RDRT_OVERWRITE)
// 		rdrt_error(token, "overwrite");
// 	else
// 		return (rdrt_core(token->value, STDOUT_FILENO,
// 			O_CREAT | O_TRUNC | O_WRONLY, 0644));
// 	return (-1);
// }
