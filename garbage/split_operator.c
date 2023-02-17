#include "minishell.h"

/**
 * @brief Abandoned due to making things way harder than it should for parser
 * 
 */

/// @note '&&' Should Have it's own parsed command, the delimiter shall be another '&&' or '||'
/**
 * This Function should be on top of the lexer and parser?,
 * 	and should not execute anything before comfirming the syntax
 * @note The data structure is mandatory for checking syntax error
 * @test
 * echo $MIKu && (echo hatsune miku && me) || echo $MIKU$MKU
*/

static const t_token	*gettoken(const t_tokenlist operators, const char *it)
{
	int	i;

	i = 0;
	while (operators[i].type != DEFAULT
		&& ft_strncmp(it, operators[i].str, ft_strlen(operators[i].str))) /* Pending optimization for operator length */
			i++;
	return (&operators[i]);
}

/**
 * Maybe. Maybe I should Make this smarter?
 * Having multiple layers make parsing really challenging
 * 
 * 
 * @brief Split each operator into each token given operatorlist,
 * and a default type or other token
 * 
 * @note 
 * Consider ignoring space to exclude unnecessary memory allocation ?
 * 	If norminette is not a concern.
 * Rather than having external fucntion to delete empty node
 * @attention
 * Condider treating space as another delimiter? Where default token will actually be individualize..
 * I think this function is gonna treat "cat < miku" '<' as default hah
 * 
 * @param input 
 * @param operators 
 * @return t_list* 
 */
t_list	*ft_split_operators(const char *input, const t_tokenlist operators)
{
	t_list			*lst_token;
	const char		*it = ft_strskip_is(input, ft_isspace) - 1;
	const t_token	*token;

	lst_token = NULL;
	while (*++it != '\0')
	{
		if (ft_isquote(*it))
		{
			it = ft_strchr(it + 1, *it);
			continue ;
		}
		token = gettoken(operators, it);
		if (token->type == DEFAULT)
			continue ;
		if (it != input)
			ft_lstadd_back(&lst_token, ft_lstnew(
				token_new(ft_substr(input, 0, it - input), DEFAULT)));
		ft_lstadd_back(&lst_token, ft_lstnew(
			token_new(ft_strdup(token->value), token->type)));
		/* Pending optimization for operator length */
		it = ft_strskip_is(it + ft_strlen(token->value), ft_isspace) - 1;
		input = it + 1;
	}
	if (it != input)
		ft_lstadd_back(&lst_token, ft_lstnew(
			token_new(ft_substr(input, 0, it - input), DEFAULT)));
	return (lst_token);
}

/**
 * @brief I think the translation should be done in the interpretor,
 * I still need parser to check for syntax error
 * 
 * @param input_raw 
 * @return t_list* 
 */
t_list	*ms_redirect_token(const char *command);

t_list	*ms_control_token(const char *input_raw)
{
	static const t_tokenlist	operators = {
	{"&&", CTRL_AND},
	{"||", CTRL_OR},
	{"(", SUBSH_BEGIN},
	{")", SUBSH_END},
	{"", DEFAULT}
	};
	t_list						*lst_control;

	lst_control = ft_split_operators(input_raw, operators);
	ft_lstiter(lst_control, lstiter_showtoken);
	for (t_list *it = lst_control; it != NULL; it = it->next)
	{
		t_token	*token = it->content;

		if (token->type == DEFAULT)
			ms_redirect_token(token->value);
	}
	ft_lstclear(&lst_control, del_token);
	return (NULL);
}

t_list	*ms_redirect_token(const char *command)
{
	static const t_tokenlist	operators = {
		{"<<", RDRT_HEREDOC},
		{">>", RDRT_APPEND},
		{"<", RDRT_INPUT},
		{">", RDRT_OVERWRITE},
		{"|", CTRL_PIPE},
		{"", DEFAULT}
	};
	t_list						*lst_redirect;

	lst_redirect = ft_split_operators(command, operators);
	ft_lstiter(lst_redirect, lstiter_showtoken);
	ft_lstclear(&lst_redirect, del_token);
	return (NULL);
}


/**
 * @brief ??
 * rdrt functions based on token
 * ctrl including pipe functions based on token
 * subsh should be interpreted in lexer?
 * I think parser should read heredoc, therefore it should know the rdrt type during parsing
 * Given that cat << a < reads before reporting syntax error
 * Might as well break these down into individual functions
 */
