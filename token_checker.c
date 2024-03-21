/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:47:12 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/03/21 21:51:24 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"
#include "libft.h"

// bool	check_parenthesis(t_token *token)
// {
// 	int		pr_cnt;

// 	pr_cnt = 0;
// 	if (token->type == sep && token->data[0] == '(')
// 		pr_cnt++;
// 	while (token->next)
// 	{
// 		if (token->next->type == sep && *(token->next->data) == '(')
// 		{
// 			if (token->type == sep || token->type == con_op)
// 				pr_cnt += 1;
// 			else
// 				return (false);
// 		}
// 		if (token->type == sep && *(token->data) == ')')
// 		{
// 			if (token->next->type == con_op || token->next->type == sep)
// 				pr_cnt -= 1;
// 			else
// 				return (false);
// 		}
// 		token = token->next;
// 	}
// 	if (token->type == sep && token->data[0] == ')')
// 		pr_cnt--;
// 	printf("%d\n", pr_cnt);
// 	if (pr_cnt != 0)
// 		return (false);
// 	return (true);
// }

// bool	check_operator(t_token *token)
// {
// 	while (token)
// 	{
// 		if (token->type == con_op)
// 			if (!(token->next == word || token->next == rdr_op))
// 				return (false);
// 		if (token->type == rdr_op)
// 			if (!(token->next) || token->next->type != word)
// 				return (false);
// 		token = token->next;
// 	}
// 	return (true);
// }

bool	check_token(t_token *token)
{
	bool	result;

	result = true;
	(void) token;
	// result = check_parenthesis(token);
	// if (result == false)
	// {
	// 	printf("pr error\n");
	// 	return (false);
	// }
	// result = check_operator(token);
	// if (result == false)
	// 	printf("op error\n");
	return (result);
}
