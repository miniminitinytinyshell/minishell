/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_standard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 19:51:17 by jaeblee           #+#    #+#             */
/*   Updated: 2024/03/25 21:09:52 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

static int	case_rdr_front(t_token *rdr, t_token **left, t_token **right)
{
	t_token	*cur;

	if (rdr->next == NULL)
		return (0);
	if (rdr->next->group != word)
		return (0);
	*right = rdr->next->next;
	rdr->next->next = NULL;
	if (*left == NULL)
		*left = rdr;
	else
	{
		cur = *left;
		while (cur->next != NULL)
			cur = cur->next;
		cur->next = rdr;
	}
	if (*right != NULL)
		if (div_std_cmd(left, right) == 0)
			return (0);
	return (1);
}

static int	case_rdr_back(t_token *rdr, t_token **left, t_token **right)
{
	t_token	*cur;

	cur = rdr;
	rdr = rdr->next;
	if (rdr->next == NULL)
		return (0);
	if (rdr->next->group != word)
		return (0);
	cur->next = rdr->next->next;
	rdr->next->next = NULL;
	if (*left == NULL)
		*left = rdr;
	else
	{
		cur = *left;
		while (cur->next != NULL)
			cur = cur->next;
		cur->next = rdr;
	}
	if (*right != NULL)
		if (div_std_cmd(left, right) == 0)
			return (0);
	return (1);
}

int	div_std_cmd(t_token **left, t_token **right)
{
	t_token	*cur;

	cur = *right;
	if (cur->group == rdr)
	{
		if (case_rdr_front(cur, left, right) == 0)
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
		if (cur->next != NULL)
			if (case_rdr_back(cur, left, right) == 0)
				return (0);
	}
	return (1);
}

int	check_std_cmd(t_tree **tree, t_token *token)
{
	t_token	*left;
	t_token	*right;

	left = NULL;
	right = token;
	(*tree)->data = NULL;
	(*tree)->type = standard_cmd;
	if (div_std_cmd(&left, &right) == 0)
		return (0);
	(*tree)->left = init_tree();
	(*tree)->right = init_tree();
	check_redirect(&(*tree)->left, left);
	check_smp_cmd(&(*tree)->right, right);
	return (1);
}
