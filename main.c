/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:35:56 by jaeblee           #+#    #+#             */
/*   Updated: 2024/03/20 19:13:04 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

// int	proc_cmd(char *cmd)
// {
// 	split_token();
// }

int	main(void)
{
	char	*cmd = "((ls&&pwd)>>infile<a<<b>c||(<< infile pwd . || ls -al *.c)) && (cat input | awk '{count}END{print count}' && echo Hello World > outfile)";

	// while (1)
	// {
	// 	cmd = get_next_line(STDIN_FILENO);
	// 	if (!cmd)
	// 		break ;
	// 	proc_cmd(cmd);
	// 	free(cmd);
	// }
	t_token *token;
	char	*token_type[4] = {"word", "sep", "con_op", "re_op"};

	token = NULL;
	tokenizer(&token, cmd);
	printf("%7s  %40s\n", "type", "data");
	printf("-------  ------------------------------------------\n");
	while (token)
	{
		printf("%-7s  [%-40s]\n", token_type[token->type], token->data);
		token = token->next;
	}
	return (0);
}
