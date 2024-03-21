/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:35:56 by jaeblee           #+#    #+#             */
/*   Updated: 2024/03/21 21:57:22 by hyeunkim         ###   ########.fr       */
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
	char	*token_type[] = {"word", "left_par", "right_par", "pipe_op", "logic_or", "logic_and", "in_trunc", "out_trunc", "here_doc", "out_append"};
	// bool	token_check;
	while (1)
	{
		cmd = readline("this is prompt : ");
		if (strcmp(cmd, "exit") == 0)
		{
			printf("exit!\n");
			break;
		}
		else
		{
			token = NULL;
			tokenizer(&token, cmd);
			// token_check = check_token(token);
			printf("%7s  %18s\n", "type", "data");
			printf("-------  ------------------------------------------\n");
			t_token	*tmp = token;
			while (tmp)
			{
				printf("%-7s  %s\n", token_type[tmp->type], tmp->data);
				tmp = tmp->next;
			}
			// if (token_check == false)
			// 	printf("####SYNTAX ERROR####\n");
			token_clear(&token);
		}
		free(cmd);
		cmd = NULL;
	}
	return (0);
}
