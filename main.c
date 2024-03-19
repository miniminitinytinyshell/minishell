/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:35:56 by jaeblee           #+#    #+#             */
/*   Updated: 2024/03/19 13:46:09 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

int	proc_cmd(char *cmd)
{
	split_token();
}

int	main(void)
{
	char	*cmd;

	while (1)
	{
		cmd = get_next_line(STDIN_FILENO);
		if (!cmd)
			break ;
		proc_cmd(cmd);
		free(cmd);
	}
	return (0);
}
