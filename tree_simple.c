/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 18:09:43 by jaeblee           #+#    #+#             */
/*   Updated: 2024/03/21 19:04:03 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

void	check_redirect(t_tree **tree, t_token *token)
{
	(*tree)->type = redirects;
	(*tree)->data = NULL;
	(*tree)->left = init_tree();
	(*tree)->left->type = rdr_op;
	(*tree)->left->data = ft_strdup(token->data);
	(*tree)->right = init_tree();
	(*tree)->right->type = name;
	(*tree)->right->data = ft_strdup(token->next->data);
	free_token_all(token);
}

void	check_args(t_tree **tree, t_token *token)
{
	char	*data;
	t_token	*cur;

	cur = token;
	data = ft_strdup(cur->data);
	while (cur->next != NULL)
	{
		cur = cur->next;
		data = ft_strjoin(cur->data);
	}
	(*tree)->data = data;
	(*tree)->type = args;
	free_token_all(token);
}

void	check_smp_cmd(t_tree **tree, t_token *token)
{
	t_token	*cur;

	cur = token->next;
	(*tree)->type = simple_cmd;
	(*tree)->data = NULL;
	(*tree)->left = init_tree();
	(*tree)->left->type = name;
	(*tree)->left->data = ft_strdup(token->data);
	(*tree)->right = init_tree();
	token = free_token(token);
	check_args(tree, cur);
}
