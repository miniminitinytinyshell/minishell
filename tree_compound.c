/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_cpd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:24:49 by jaeblee           #+#    #+#             */
/*   Updated: 2024/03/21 18:33:04 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

void	div_std_cmd(t_tree **tree, t_token *left, t_token *right, int wd)
{
	t_token *cur;

	(*tree)->data = NULL;
	(*tree)->type = standard_cmd;
	(*tree)->left = init_tree();
	(*tree)->right = init_tree();
	if (wd == 0)
	{
		cur = left->next;
		right = cur->next;
		cur->next = NULL;
		check_redirect(&(*tree)->left, left);
		check_std_cmd(&(*tree)->right, right);
	}
	else
	{
		cur = right;
		right = right->next;
		cur->next = right->next->next;
		right->next->next = NULL;
		check_redirect(&(*tree)->left, right);
		check_std_cmd(&(*tree)->right, left);
	}
}

void	check_std_cmd(t_tree **tree, t_token *token)
{
	t_token *cur;

	cur = token;
	if (cur->type == re_op)
		div_std_cmd(tree, token, cur, 0);
	while (cur->next != NULL)
	{
		if (cur->next->type == re_op)
			break ;
		cur = cur->next;
	}
	if (cur->next == NULL)
		check_smp_cmd(tree, token);
	else
		div_std_cmd(tree, token, cur, 1);
}

void	div_cpd_cmd(t_tree **tree, t_token *left, t_token *right, int pr)
{
	t_token	*cur;

	cur = right;
	(*tree)->data = ft_strdup(right->data);
	(*tree)->type = compound_cmd;
	right = right->next;
	cur = free_token(cur);
	(*tree)->left = init_tree();
	(*tree)->right = init_tree();
	if (pr == 0)
		check_std_cmd(&(*tree)->left, left);
	else
		check_cpd_cmd(&(*tree)->left, left); // 괄호 없애기 추가
	check_cpd_cmd(&(*tree)->right, right);
}

void	check_cpd_cmd(t_tree **tree, t_token *token)
{
	int		pr;
	t_token	*cur;

	pr = 0;
	cur = token;
	if (cur->type == sep)
		skip_sep();
	while (cur->type != con_op && cur->next != NULL)
		cur = cur->next;
	if (cur->type == con_op)
		div_cpd_cmd(tree, token, cur, pr);
	else
	{
		if (pr == 0)
			check_std_cmd(tree, token);
		else
			check_cpd_cmd(tree, token); // 괄호 없애기 추가
	}
}
