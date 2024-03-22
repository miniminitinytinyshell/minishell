/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_compound.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:24:49 by jaeblee           #+#    #+#             */
/*   Updated: 2024/03/22 15:53:56 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"
// #include "libft.h"

static int	div_cpd_cmd(t_tree **tree, t_token *left, t_token *right, int pr)
{
	t_token	*cur;

	cur = right;
	right = right->next;
	cur->next = NULL;
	(*tree)->data = ft_strdup(right->data);
	(*tree)->type = compound_cmd;
	cur = right;
	right = right->next;
	cur = token_free(cur);
	(*tree)->left = init_tree();
	(*tree)->right = init_tree();
	if (pr == 0)
		if (check_std_cmd(&(*tree)->left, left) == 0)
			return (0);
	else
		if (check_cpd_cmd(&(*tree)->left, erase_pr(left)) == 0)
			return (0);
	if (check_cpd_cmd(&(*tree)->right, right) == 0)
		return (0);
	return (1);
}

static int case_sep(t_tree **tree, t_token *token)
{
	t_token	*cur;

	cur = token;
	if (skip_sep(&token) == 0)
		return (0);
	if (cur->next == NULL)
		if (check_cpd_cmd(tree, erase_pr_pr(token)) == 0)
			return (0);
	if (cur->next->group == con)
		if (div_cpd_cmd(tree, token, cur, true) == 0)
			return (0);
	else
		return (0);
	return (1);
}

static int	case_etc(t_tree **tree, t_token *token)
{
	t_token	*cur;

	cur = token;
	while (cur->next != NULL)
	{
		if (cur->next->group == con)
			break ;
		if (cur->next->group == sep)
			return (0);
		cur = cur->next;
	}
	if (cur->next == NULL)
		if (check_std_cmd(tree, token) == 0)
			return (0);
	else
		if (div_cpd_cmd(tree, token, cur, false) == 0)
			return (0);
	return (1);
}

int	check_cpd_cmd(t_tree **tree, t_token *token)
{
	if (token->group == con)
		return (0);
	if (token->group == sep)
		if (case_sep(tree, token) == 0)
			return (0);
	else
		if (case_etc(tree, token) == 0)
			return (0);
	return (1);
}
