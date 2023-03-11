/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 12:16:10 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/11 23:21:26 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	parse_default(t_ctrl *ctrl, t_list **lst_token, t_ftctrl *condition)
{
	t_list	*node;
	t_token	*token;

	node = ft_lstextract_front(lst_token);
	token = node->content;
	ft_lstadd_back(&ctrl->lst_args, ft_lstnew(token->value));
	ft_lstdelone(node, free);
	(void)condition;
	return (0);
}

typedef int	(*t_ftparse)(t_ctrl *ctrl, t_list **lst_token, t_ftctrl *condition);

typedef struct s_parselst
{
	int			type;
	t_ftparse	ft_parse;
}			t_parselst;

int	find_ftparse(unsigned int i, const void *parselst, const void *p_type)
{
	const int	lsttype = ((t_parselst *)parselst)[i].type;

	return (lsttype == *(int *)p_type);
}

static int	parser_tokentype(t_ctrl *ctrl, t_list **lst_token,
			t_ftctrl *condition)
{
	static const t_parselst	arr_ftparse[] = {
	{.type = DEFAULT, .ft_parse = parse_default},
	{.type = RDRT, .ft_parse = parse_rdrt},
	{.type = CTRL, .ft_parse = parse_ctrl},
	{.type = SUBSH_BEGIN, .ft_parse = parse_subshbegin},
	{.type = SUBSH_END, .ft_parse = parse_subshend},
	};
	const t_token			*token = (*lst_token)->content;
	unsigned int			i;

	i = -1;
	while (++i < sizeof(arr_ftparse) / sizeof(arr_ftparse[0]))
	{
		if (token->type == arr_ftparse[i].type)
			return (arr_ftparse[i].ft_parse(ctrl, lst_token, condition));
	}
	lstname_token("Unknown token type");
	lstshow_lexertoken((void *)token);
	exit(39);
	return (-1);
}

t_list	*ms_parser(t_list **lst_token)
{
	t_list		*lst_ctrl;
	t_ftctrl	condition;
	t_ctrl		*ctrl;

	lst_ctrl = NULL;
	condition = ctrl_continue;
	while (*lst_token != NULL && condition != NULL)
	{
		ctrl = ctrl_new(*condition, exe_argv, free);
		while (*lst_token != NULL
			&& parser_tokentype(ctrl, lst_token, &condition) == 0)
			;
		ft_lstadd_back(&lst_ctrl, ft_lstnew(ctrl));
	}
	return (lst_ctrl);
}
