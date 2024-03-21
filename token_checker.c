/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:47:12 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/03/21 18:44:16 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"
#include "libft.h"

bool	check_parenthesis(t_token *token)
{
	int		pr_cnt;

	pr_cnt = 0;
	while (token->next)
	{
		if (token->next->type == sep && *(token->next->data) == '(')
		{
			if (token->type != con_op)
				return (false);
			else
				pr_cnt += 1;
		}
		if (token->type == sep && *(token->data) == ')')
		{
			if (token->next->type != con_op)
				return (false);
			else
				pr_cnt -= 1;
		}
		token = token->next;
	}
	if (pr_cnt != 0)
		return (false);
	return (true);
}

bool	check_operator(t_token *token)
{
	while (token)
	{
		if (token->type == con_op)
			if (!(token->next) || token->next->type == con_op)
				return (false);
		if (token->type == re_op)
			if (!(token->next) || token->next->type != word)
				return (false);
	}
	return (true);
}

bool	check_token(t_token *token)
{
	bool	result;

	result = check_parenthesis(token);
	if (result == false)
		return (false);
	result = check_operator(token);
	return (result);
}
