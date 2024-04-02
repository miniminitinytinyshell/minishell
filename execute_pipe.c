/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:29:36 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/02 17:32:56 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

void	process_pipe(t_tree **tree, char **envp, int *status)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		error_pipe();
	pid = fork();
	if (pid == -1)
		error_fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execute_cpd_cmd(&(*tree)->left, envp, status);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, status, 0);
		*status = WEXITSTATUS(*status);
		execute_cpd_cmd(&(*tree)->right, envp, status);
	}
	exit(*status);
}

void	execute_pipe(t_tree **tree, char **envp, int *status)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error_fork();
	if (pid == 0)
		process_pipe(tree, envp, status);
	else
	{
		waitpid(pid, status, 0);
		*status = WEXITSTATUS(*status);
	}
}
