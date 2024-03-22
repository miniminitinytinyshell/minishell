/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_standard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:24:49 by jaeblee           #+#    #+#             */
/*   Updated: 2024/03/22 17:35:33 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

static int	case_rdr_front(t_tree **tree, t_token *left, t_token *right)
{
	t_token	*cur;

	cur = left->next;
	if (cur->next == NULL)
	{
		if (check_redirect(&(*tree)->left, left) == 0)
			return (0);
	}
	else
	{
		right = cur->next;
		cur->next = NULL;
		(*tree)->right = init_tree();
		if (check_redirect(&(*tree)->left, left) == 0)
			return (0);
		if (check_std_cmd(&(*tree)->right, right) == 0)
			return (0);
	}
	return (1);
}

static int	case_rdr_back(t_tree **tree, t_token *left, t_token *right)
{
	t_token	*cur;

	cur = right;
	right = right->next;
	cur->next = right->next->next;
	right->next->next = NULL;
	if (check_redirect(&(*tree)->left, right) == 0)
		return (0);
	if (check_std_cmd(&(*tree)->right, left) == 0)
		return (0);
	return (1);
}

static int	div_std_cmd(t_tree **tree, t_token *left, t_token *right, int wd)
{
	t_token *cur;

	if (wd == 0)
		cur = right;
	else
		cur = right->next;
	if (cur->next == NULL)
		return (0);
	if (cur->next->group != word)
		return (0);
	(*tree)->data = NULL;
	(*tree)->type = standard_cmd;
	(*tree)->left = init_tree();
	if (wd == 0)
	{
		if (case_rdr_front(tree, left, right) == 0)
			return (0);
	}
	else
	{
		(*tree)->right = init_tree();
		if (case_rdr_back(tree, left, right) == 0)
			return (0);
	}
	return (1);
}

int	check_std_cmd(t_tree **tree, t_token *token)
{
	t_token *cur;

	cur = token;
	if (cur->group == rdr)
	{
		if (div_std_cmd(tree, token, cur, 0) == 0)
			return (0);
	}
	else
	{
		while (cur->next != NULL)
		{
			if (cur->next->group == rdr)
				break ;
			cur = cur->next;
		}
		if (cur->next == NULL)
		{
			if (check_smp_cmd(tree, token) == 0)
				return (0);
		}
		else
			if (div_std_cmd(tree, token, cur, 1) == 0)
				return (0);
	}
	return (1);
}
