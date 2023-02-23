#include "minishell.h"

static char	*heredoc(const char *limiter_src)
{
	t_list	*lst_buffer;
	char	*limiter;
	char	*input;

	lst_buffer = NULL;
	limiter = ft_strjoin(limiter_src, "\n");
	while (1)
	{
		/* The history */
		input = readline("heredoc> ");
		if (input == NULL || !ft_strcmp(limiter, input))
			break ;
		ft_lstadd_back(&lst_buffer, ft_lstnew(input));
	}
	free(input);
	free(limiter);
	return (ft_lsttostr_delimiter_clear(&lst_buffer, "\n"));
}

static int	heredoc_limiter(char *limiter)
{
	int	hasquote;

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
	return (!hasquote);
}

/* This is so cursed and awesome at the same time */
static char	*heredoc_expand(const char *str, const char *casted_envp)
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

char	*parser_heredoc(char **envp, char *limiter)
{
	char	*str_content;
	int		expand;

	expand = heredoc_limiter(limiter);
	str_content = heredoc(limiter);
	free(limiter);
	if (expand)
		return (ft_strmodify(heredoc_expand, str_content, (void *)envp));
	else
		return (str_content);
}
