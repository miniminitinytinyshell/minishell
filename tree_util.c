/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 18:00:36 by jaeblee           #+#    #+#             */
/*   Updated: 2024/03/26 17:28:38 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

t_tree	*init_tree(void)
{
	t_tree	*temp;

	temp = (t_tree *)malloc(sizeof(t_tree));
	temp->data = NULL;
	temp->left = NULL;
	temp->right = NULL;
	return (temp);
}

t_tree	*free_tree(t_tree *tree)
{
	if (tree->left)
		tree->left = free_tree(tree->left);
	if (tree->right)
		tree->right = free_tree(tree->right);
	if (tree->data != NULL)
		free(tree->data);
	free(tree);
	tree = NULL;
	return (tree);
}

// t_token	*erase_pr(t_token *token)
// {
// 	int		cnt;
// 	t_token	*cur;
// 	t_token	*temp;

// 	cnt = 1;
// 	cur = token;
// 	while (cur->next->group == sep && cur->next->data[0] == '(')
// 	{
// 		cnt++;
// 		cur = cur->next;
// 	}
// 	temp = token;
// 	token = token->next;
// 	temp = token_free(temp);
// 	while (cur->next != NULL)
// 	{
// 		if (cur->next->group == sep && cur->next->data[0] == '(')
// 			cnt++;
// 		if (cur->next->group == sep && cur->next->data[0] == ')')
// 			cnt--;
// 		if (cnt == 0)
// 			break ;
// 		cur = cur->next;
// 	}
// 	temp = cur->next;
// 	temp = token_free(temp);
// 	cur->next = NULL;
// 	return (token);
// }

t_token	*erase_pr(t_token *token)
{
	int		cnt;
	t_token	*cur;
	t_token	*temp;

	temp = token;
	token = token->next;
	temp = token_free(temp);
	if (token->group == sep && token->data[0] == '(')
		cnt = 2;
	else
		cnt = 1;
	cur = token;
	while (cur->next)
	{
		if (cur->next->group == sep && cur->next->data[0] == '(')
			cnt++;
		if (cur->next->group == sep && cur->next->data[0] == ')')
			cnt--;
		if (cnt == 0)
			break ;
		cur = cur->next;
	}
	temp = cur->next;
	cur->next = token_free(temp);
	return (token);
}

int	skip_sep(t_token **token)
{
	int	pr_cnt;

	pr_cnt = 0;
	while (*token)
	{
		if ((*token)->group == sep && (*token)->data[0] == '(')
			pr_cnt++;
		if ((*token)->group == sep && (*token)->data[0] == ')')
			pr_cnt--;
		if (pr_cnt == 0)
			break ;
		if (pr_cnt < 0)
			return (0);
		*token = (*token)->next;
	}
	if (pr_cnt == 0)
		return (1);
	return (0);
}
