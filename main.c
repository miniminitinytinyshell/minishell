/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:35:56 by jaeblee           #+#    #+#             */
/*   Updated: 2024/03/21 18:59:13 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"
#include "libft.h"

// int	proc_cmd(char *cmd)
// {
// 	split_token();
// }

int	main(void)
{
	char	*cmd;
	t_token *token;
	char	*token_type[4] = {"word", "sep", "con_op", "re_op"};
	cmd = "(ls && ls) out";
	token = NULL;
	tokenizer(&token, cmd);
	bool	token_check = check_token(token);
			printf("%7s  %40s\n", "type", "data");
	printf("-------  ------------------------------------------\n");
	t_token	*tmp = token;
	while (tmp)
	{
		printf("%-7s  [%s\n", token_type[tmp->type], tmp->data);
		tmp = tmp->next;
	}
	if (token_check == false)
		printf("####SYNTAX ERROR####\n");
	token_clear(&token);
	return (0);
}
