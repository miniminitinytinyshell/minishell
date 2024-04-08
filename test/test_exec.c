/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:48:47 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/08 16:30:21 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int	main(int ac, char **av, char **envp)
{
	ac = 0;
	av = NULL;
	char *cmd1[] = {"/bin/ls", NULL};
	char *cmd2[] = {"/usr/bin/touch", "./.././touch", NULL};

	execve(*cmd1, cmd1, envp);
	printf("CLEAR\n");
	return (0);
}
