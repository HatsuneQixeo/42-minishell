#include "minishell.h"
#define ERR	((void *)-1)

int	closing_parenthesis(const char *it); // ?
int	closing_parenthesis(const char *it)
{
	static int	paren;
	int			clear;

	if (it == NULL)
	{
		clear = paren;
		paren = 0;
		return (clear);
	}
	else if (*it == '(')
		paren++;
	else if (*it == ')')
		paren--;
	return (paren);
}

/* ? Should this include a delimiter? */
char	*ft_strmultiply(const char *src, int amount)
{
	char			*str;
	const size_t	len = ft_strlen(src);
	const size_t	total_len = len * amount;

	if (total_len == 0)
		return (ft_strdup(""));
	str = malloc(total_len);
	if (str == NULL)
		return (NULL);
	str[0] = '\0';
	while (amount--)
		ft_strlcat(str, src, total_len + 1);
	return (str);
}

char	closing_quote(const char *it)
{
	static char	quote;
	char		clear;

	if (it == NULL)
	{
		clear = quote;
		quote = '\0';
		return (clear);
	}
	else if (!ft_isquote(*it))
		return (quote);
	else if (quote == '\0')
		quote = *it;
	else if (quote == *it)
		quote = '\0';
	return (quote);
}

// subsh is suppose to represent the amount of unclosed subsh
static const char	*missing(void)
{
	static const char	*missing[] = {
		NULL,
		"quote> ",
		"dquote> ",
		"subsh> ",
		"subsh quote> ",
		"subsh dquote> "
	};
	char				quote;
	int					index;

	quote = closing_quote(NULL);
	index = ((quote == '\'') || ((quote == '\"') * 2));
	index += ((closing_parenthesis(NULL) != 0) * 3);
	return (missing[index]);
}

static const char	*missing_closing_character(const char *input_raw)
{
	const char	*it = &input_raw[-1];

	while (*++it != '\0')
	{
		if (closing_quote(it))
			continue;
		else if (closing_parenthesis(it) == -1)
		{
			closing_parenthesis(NULL);
			closing_quote(NULL);
			ft_dprintf(2,
				MINISHELL": %s: Closing parenthesis without opening\n", it);
			return (ERR);
		}
	}
	return (missing());
}

char	*ms_closequote(const char *input_raw)
{
	char		*input;
	char		*read;
	const char	*ret;

	input = ft_strdup(input_raw);
	while (1)
	{
		ret = missing_closing_character(input);
		if (ret == ERR)
			break ;
		else if (ret == NULL)
			return (input);
		/* This readline inherits the history,
			maybe I should find a way to disable that*/
		read = readline(ret);
		if (read == NULL)
			break ;
		input = ft_strmodify(ft_strjoin, input, "\n");
		input = ft_strcombine(input, read);
	}
	free(input);
	return (NULL);
}
