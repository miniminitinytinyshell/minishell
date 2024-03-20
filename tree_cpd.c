/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_cpd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:24:49 by jaeblee           #+#    #+#             */
/*   Updated: 2024/03/20 18:55:54 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

int	skip_separ_rdt(t_token **token)
{
	int		count;
	t_token	*cur;

	count = 1;
	cur = *token;
	if (cur->data[0] == ')')
		return (0);
	while (count > 0 && cur->next != NULL)
	{
		cur = cur->next;
		if (cur->type == sep && cur->data[0] == '(')
			count++;
		else if (cur->type == sep && cur->data[0] == ')')
			count--;
	}
	if (count != 0)
		return (0);
	*token = cur;
	return (1);
}

void	cpd_separ_rdt(t_tree **tree, t_token *left, t_token *right)
{
	t_token	*cur;

	cur = left;
	while (cur->next == right)
		cur = cur->next;
	cur->next = NULL;
	(*tree)->type = compound_cmd;
	(*tree)->data = ft_strdup(right->data);
	(*tree)->left = init_tree();
	(*tree)->right = init_tree();
	cpd_check_rdt(&(*tree)->left, left);
	// 두 경우의 수(Redirection이 cmd 앞/뒤) 생각해야 함
}

int	cpd_check_rdt(t_tree **tree, t_token *token)
{
	t_token	*cur;

	cur = token;
	while (cur->type != re_op && cur->next != NULL)
	{
		if (cur->type = sep)
			skip_sep(&cur);
		cur = cur->next;
	}
	if (cur->type == re_op)
		cpd_separ_rdt(tree, token, cur);
	else
		cpd_check_ctl(tree, token); // 괄호 없애기 추가해야 됨
}

void	cpd_separ_ctl(t_tree **tree, t_token *left, t_token *right, int pr)
{
	t_token	*cur;

	cur = right;
	right = right->next;
	(*tree)->type = compound_cmd;
	(*tree)->data = ft_strdup(cur->data);
	cur = free_token(cur);
	(*tree)->left = init_tree();
	(*tree)->right = init_tree();
	if (pr == 1)
		cpd_check_rdt(&(*tree)->left, left);
	else
		std_check_rdt(&(*tree)->left, left);
	cpd_check_ctl(&(*tree)->right, right);
}

int	cpd_check_ctl(t_tree **tree, t_token *token)
{
	int		pr;
	t_token	*cur;

	pr = 0;
	cur = token;
	while (cur->type != con_op && cur->next != NULL)
	{
		if (cur->type == sep)
		{
			pr = skip_sep(&cur);
			if (pr == 0)
				return (0);
		}
		cur = cur->next;
	}
	if (cur->type == con_op)
		sep_token(tree, token, cur, pr);
	else if (pr == 1)
		cpd_check_rdt(tree, token);
	else
		std_check_rdt();
}
