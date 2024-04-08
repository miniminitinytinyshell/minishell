/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:29:36 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/08 18:26:44 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

void	process_pipe(t_tree **tree, t_envp *envp, int *status)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		error_syscall();
	pid = fork();
	if (pid == -1)
		error_syscall();
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
		execute_cpd_cmd(&(*tree)->right, envp, status);
		waitpid(pid, status, 0);
		*status = WEXITSTATUS(*status);
	}
	exit(*status);
}

void	execute_pipe_cmd(t_tree **tree, t_envp *envp, int *status)
{
	if ((*tree)->type == standard_cmd)
		execute_std_cmd(tree, envp, status);
	else if ((*tree)->type == compound_cmd)
	{
		if (ft_strncmp((*tree)->oper, "&&", 3) == 0)
		{
			execute_pipe_cmd(&(*tree)->left, envp, status);
			if (*status == 0)
				execute_pipe_cmd(&(*tree)->right, envp, status);
		}
		else if (ft_strncmp((*tree)->oper, "||", 3) == 0)
		{
			execute_pipe_cmd(&(*tree)->left, envp, status);
			if (*status != 0)
				execute_pipe_cmd(&(*tree)->right, envp, status);
		}
		else
			process_pipe(tree, envp, status);
	}
}

void	execute_pipe(t_tree **tree, t_envp *envp, int *status)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error_syscall();
	if (pid == 0)
	{
		set_child_signal();
		process_pipe(tree, envp, status);
	}
	else
	{
		set_parent_signal();
		waitpid(pid, status, 0);
		*status = WEXITSTATUS(*status);
	}
}
