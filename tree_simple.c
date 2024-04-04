/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 18:09:43 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/04 14:52:53 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

int	check_rdr_cmd(t_tree **tree, t_token *token)
{
	(*tree)->type = rdr_cmd;
	(*tree)->data = (char **)malloc(sizeof(char *) * 3);
	(*tree)->data[0] = ft_strdup(token->data);
	(*tree)->data[1] = ft_strdup(token->next->data);
	(*tree)->data[2] = NULL;
	token_clear(&token);
	return (1);
}

int	check_redirect(t_tree **tree, t_token *token)
{
	t_token	*cur;

	(*tree)->type = redirects;
	(*tree)->data = NULL;
	cur = token->next->next;
	token->next->next = NULL;
	(*tree)->left = init_tree();
	check_rdr_cmd(&(*tree)->left, token);
	if (cur != NULL)
	{
		(*tree)->right = init_tree();
		check_redirect(&(*tree)->right, cur);
	}
	else
		(*tree)->right = NULL;
	return (1);
}

int	check_smp_cmd(t_tree **tree, t_token *token)
{
	int		i;
	int		size;
	t_token	*cur;

	i = 0;
	cur = token;
	size = get_token_size(token);
	(*tree)->type = simple_cmd;
	(*tree)->data = (char **)malloc(sizeof(char *) * (size + 1));
	if ((*tree)->data == NULL)
	{
		token_clear(&token);
		return (error_malloc());
	}
	while (i < size)
	{
		(*tree)->data[i] = ft_strdup(cur->data);
		cur = cur->next;
		i++;
	}
	(*tree)->data[i] = NULL;
	token_clear(&token);
	return (1);
}
