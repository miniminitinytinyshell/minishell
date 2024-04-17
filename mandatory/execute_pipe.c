/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:29:36 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/17 16:31:42 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

static int	count_pipe(t_tree *tree)
{
	int		cnt;
	t_tree	*cur;

	cnt = 0;
	cur = tree;
	while (cur)
	{
		if (cur->type == compound_cmd)
			if (cur->oper[0] == '|')
				cnt++;
		cur = cur->right;
	}
	return (cnt);
}

static pid_t	proc_fork(t_tree **tree, t_envp *envp, int *status, int *old_fd)
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
		if (*old_fd != -1)
			dup2(*old_fd, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execute_cpd_cmd(&(*tree)->left, envp, status);
		exit(*status);
	}
	close(fd[1]);
	*old_fd = fd[0];
	return (pid);
}

static pid_t	last_fork(t_tree **tree, t_envp *envp, int *status, int *old_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error_syscall();
	if (pid == 0)
	{
		dup2(*old_fd, STDIN_FILENO);
		close(*old_fd);
		execute_cpd_cmd(tree, envp, status);
		exit(*status);
	}
	close(*old_fd);
	return (pid);
}

void	process_pipe(t_tree **tree, t_envp *envp, int *status)
{
	int		i;
	int		fd;
	int		count;
	pid_t	*pids;

	i = 0;
	fd = -1;
	count = count_pipe(*tree);
	pids = ft_calloc(count + 1, sizeof(pid_t));
	while (i < count)
	{
		pids[i] = proc_fork(tree, envp, status, &fd);
		tree = &(*tree)->right;
		i++;
	}
	pids[i] = last_fork(tree, envp, status, &fd);
	i = 0;
	while (i <= count)
	{
		waitpid(pids[i], status, 0);
		i++;
	}
	set_status(status);
}

void	execute_pipe(t_tree **tree, t_envp *envp, int *status)
{
	// signal(SIGPIPE, SIG_IGN);
	process_pipe(tree, envp, status);
}
