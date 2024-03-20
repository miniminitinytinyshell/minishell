/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:35:56 by jaeblee           #+#    #+#             */
/*   Updated: 2024/03/20 13:09:05 by hyeunkim         ###   ########.fr       */
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
	char	*cmd = "(<<infile pwd . || ls -al *.c) && (cat input | awk '{count}END{print count}' && echo Hello World > outfile)";

	// while (1)
	// {
	// 	cmd = get_next_line(STDIN_FILENO);
	// 	if (!cmd)
	// 		break ;
	// 	proc_cmd(cmd);
	// 	free(cmd);
	// }
	printf("%d\n", count_token(cmd));
	return (0);
}
