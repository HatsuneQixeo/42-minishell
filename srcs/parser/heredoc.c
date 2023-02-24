#include "minishell.h"

/* Return 0 is given limiter has no quote, 1 if has quote */
int	heredoc_limiter(char *limiter)
{
	int	hasquote;

	hasquote = 0;
	while (*limiter != '\0')
	{
		if (!ft_isquote(*limiter))
		{
			limiter++;
			continue ;
		}
		ft_memmove(limiter, limiter + 1, ft_strlen(limiter + 1) + 1);
		hasquote = 1;
	}
	return (hasquote);
}

t_list	*heredoc(const char *limiter)
{
	t_list	*lst_buffer;
	char	*input;

	lst_buffer = NULL;
	while (1)
	{
		input = readline("heredoc> ");
		if (input == NULL || !ft_strcmp(limiter, input))
			break ;
		ft_lstadd_back(&lst_buffer, ft_lstnew(input));
	}
	free(input);
	return (lst_buffer);
}

/* This is so cursed and awesome at the same time */
/* Hah, not anymore */
char	*heredoc_expand_arg(const char *str, const char *casted_envp)
{
	t_list		*lst_expanded;
	const char	*ptr_var;
	char		**envp;

	lst_expanded = NULL;
	envp = (void *)casted_envp;
	while (1)
	{
		ptr_var = ft_strchr(str, '$');
		if (ptr_var == NULL)
			break ;
		ft_lstadd_back(&lst_expanded, ft_lstnew(
				ft_substr(str, 0, ptr_var - str)));
		ft_lstadd_back(&lst_expanded, ft_lstnew(
				expand_var(envp, &ptr_var)));
		str = ptr_var + 1;
	}
	ft_lstadd_back(&lst_expanded, ft_lstnew(ft_strdup(str)));
	return (ft_lsttostr_clear(&lst_expanded));
}

void	heredoc_expand_lst(char **envp, t_list *lst)
{
	while (lst != NULL)
	{
		lst->content = ft_strmodify(
				heredoc_expand_arg, lst->content, (void *)envp);
		lst = lst->next;
	}
}
