/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_standard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 19:51:17 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/01 22:04:36 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

static int	case_rdr_front(t_token *rdr, t_token **left, t_token **right)
{
	t_token	*cur;

	if (rdr->next == NULL)
		return (error_syntax(rdr->data, right, 0));
	if (rdr->next->group != word)
		return (error_syntax(rdr->next->data, right, 0));
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
		return (error_syntax(rdr->data, right, 0));
	if (rdr->next->group != word)
		return (error_syntax(rdr->next->data, right, 0));
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

	if (token == NULL)
		return (0);
	left = NULL;
	right = token;
	(*tree)->type = standard_cmd;
	if (div_std_cmd(&left, &right) == 0)
		return (0);
	if (left != NULL)
	{
		(*tree)->left = init_tree();
		check_redirect(&(*tree)->left, left);
	}
	if (right != NULL)
	{
		(*tree)->right = init_tree();
		if (check_smp_cmd(&(*tree)->right, right) == 0)
			return (0);
	}
	return (1);
}
