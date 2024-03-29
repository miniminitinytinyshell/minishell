/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 18:09:43 by jaeblee           #+#    #+#             */
/*   Updated: 2024/03/22 16:48:17 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

int	check_redirect(t_tree **tree, t_token *token)
{
	(*tree)->type = redirects;
	(*tree)->data = NULL;
	(*tree)->left = init_tree();
	(*tree)->left->type = rdr_op;
	(*tree)->left->data = ft_strdup(token->data);
	(*tree)->right = init_tree();
	(*tree)->right->type = name;
	(*tree)->right->data = ft_strdup(token->next->data);
	token_clear(&token);
	return (1);
}

int	check_args(t_tree **tree, t_token *token)
{
	char	*data;
	t_token	*cur;

	cur = token;
	data = NULL;
	while (cur != NULL)
	{
		if (data == NULL)
			data = ft_strdup(cur->data);
		else
		{
			data = ft_strjoin(data, " ");
			data = ft_strjoin(data, cur->data);
		}
		cur = cur->next;
	}
	(*tree)->data = data;
	(*tree)->type = args;
	token_clear(&token);
	return (1);
}

int	check_smp_cmd(t_tree **tree, t_token *token)
{
	t_token	*cur;

	cur = token->next;
	(*tree)->type = simple_cmd;
	(*tree)->data = NULL;
	(*tree)->left = init_tree();
	(*tree)->left->type = name;
	(*tree)->left->data = ft_strdup(token->data);
	(*tree)->right = init_tree();
	token = token_free(token);
	check_args(&(*tree)->right, cur);
	return (1);
}
