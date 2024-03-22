/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 18:00:36 by jaeblee           #+#    #+#             */
/*   Updated: 2024/03/22 15:42:31 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

t_tree	*init_tree(void)
{
	t_tree	*temp;

	temp = (t_tree *)malloc(sizeof(t_tree));
	temp->left = NULL;
	temp->right = NULL;
	return (temp);
}

t_token	*erase_pr(t_token *token)
{
	t_token *cur;
	t_token *temp;

	temp = token;
	token = token->next;
	cur = token;
	temp = free_token(temp);
	while (cur->next->group == sep)
		cur = cur->next;
	temp = cur->next;
	temp = free_token(temp);
	cur->next = NULL;
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
