/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:22:32 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/16 17:24:35 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

static int	div_pipe(t_tree **tree, t_token *left, t_token *right)
{
	t_token	*cur;

	cur = right;
	right = right->next;
	if (!right->next)
		return (error_syntax(right->data, &left, 0));
	cur->next = NULL;
	(*tree)->oper = ft_strdup(right->data);
	if (!(*tree)->oper)
		error_syscall();
	(*tree)->type = compound_cmd;
	cur = right;
	right = right->next;
	cur = token_free(cur);
	(*tree)->left = init_tree();
	(*tree)->right = init_tree();
	if (check_cpd_cmd(&(*tree)->left, left) == 0)
		return (token_clear(&right));
	if (check_pipe(&(*tree)->right, right) == 0)
		return (0);
	return (1);
}

int	check_next_pipe(t_tree **tree, t_token *token, t_token *cur)
{
	if (cur->next == NULL)
	{
		if (check_cpd_cmd(tree, token) == 0)
			return (0);
	}
	else
		if (div_pipe(tree, token, cur) == 0)
			return (0);
	return (1);
}

int	check_pipe(t_tree **tree, t_token *token)
{
	t_token	*cur;

	if (!token)
		return (0);
	cur = token;
	if (cur->group == sep)
		if (skip_sep(&cur) == 0)
			return (error_syntax("(", &token, '('));
	if (cur->group == con)
		return (error_syntax(token->data, &token, 0));
	while (cur->next)
	{
		if (cur->next->group == con && ft_strncmp(cur->next->data, "|", 2) != 0)
			break ;
		cur = cur->next;
		if (cur->group == sep)
			if (skip_sep(&cur) == 0)
				return (error_syntax("(", &token, '('));
	}
	if (check_next_pipe(tree, token, cur) == 0)
		return (0);
	return (1);
}
