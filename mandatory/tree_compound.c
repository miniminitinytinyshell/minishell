/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_compound.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:24:49 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/18 14:43:30 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

static int	div_cpd_cmd(t_tree **tree, t_token *left, t_token *right, int pr)
{
	t_token	*cur;

	cur = right;
	right = right->next;
	if (!right->next)
		return (error_syntax(right->data, &left, 0));
	cur->next = NULL;
	(*tree)->oper = ft_strdup(right->data);
	(*tree)->type = compound_cmd;
	cur = right;
	right = right->next;
	cur = token_free(cur);
	(*tree)->left = init_tree();
	(*tree)->right = init_tree();
	if (pr == 0)
	{
		if (check_std_cmd(&(*tree)->left, left) == 0)
			return (token_clear(&right));
	}
	else
		if (check_cpd_cmd(&(*tree)->left, erase_pr(left)) == 0)
			return (token_clear(&right));
	if (check_cpd_cmd(&(*tree)->right, right) == 0)
		return (0);
	return (1);
}

static int	case_sep(t_tree **tree, t_token *token)
{
	t_token	*cur;

	cur = token;
	if (skip_sep(&cur) == 0)
		return (error_syntax("(", &token, '('));
	if (cur->next == NULL)
	{
		if (check_cpd_cmd(tree, erase_pr(token)) == 0)
			return (0);
	}
	else if (cur->next->group == con)
	{
		if (div_cpd_cmd(tree, token, cur, true) == 0)
			return (0);
	}
	else
		return (error_syntax(cur->next->data, &token, 0));
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
			return (error_syntax(cur->next->data, &token, 0));
		cur = cur->next;
	}
	if (cur->next == NULL)
	{
		if (check_std_cmd(tree, token) == 0)
			return (0);
	}
	else
		if (div_cpd_cmd(tree, token, cur, false) == 0)
			return (0);
	return (1);
}

int	check_cpd_cmd(t_tree **tree, t_token *token)
{
	if (token == NULL)
		return (0);
	if (token->group == con)
		return (error_syntax(token->data, &token, 0));
	if (token->group == sep)
	{
		if (case_sep(tree, token) == 0)
			return (0);
	}
	else
		if (case_etc(tree, token) == 0)
			return (0);
	return (1);
}
