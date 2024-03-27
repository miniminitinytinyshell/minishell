/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:48:47 by jaeblee           #+#    #+#             */
/*   Updated: 2024/03/27 18:53:55 by jaeblee          ###   ########.fr       */
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
	char *cmd1[] = {"/usr/bin/touch", "/Users/jaeblee/42Cursus/Team_Prj/minishell/test/./.././touch", NULL};
	char *cmd2[] = {"/usr/bin/touch", "./.././touch", NULL};

	execve(*cmd1, cmd1, envp);
	return (0);
}
