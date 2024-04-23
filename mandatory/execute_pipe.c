/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:29:36 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/18 15:53:20 by hyeunkim         ###   ########.fr       */
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

static void	execute_pipe_cmd(t_tree **tree, t_envp *envp, int *status)
{
	if ((*tree)->type == compound_cmd)
	{
		ft_putstr_fd("mongshll: ", STDERR_FILENO);
		ft_putendl_fd("parenthesis only for priorities", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	else
	{
		*status = expand_tree(tree, envp->data, *status);
		if (*status != 0)
			exit(*status);
		if (find_builtin((*tree)->right))
			execute_builtin(*tree, envp, status);
		else
		{
			signal(SIGINT, SIG_DFL);
			if (execute_rdr((*tree)->left, status))
				execute_cmd((*tree)->right, envp);
		}
		exit(*status);
	}
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
		{
			dup2(*old_fd, STDIN_FILENO);
			close(*old_fd);
		}
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execute_pipe_cmd(&(*tree)->left, envp, status);
	}
	close(fd[1]);
	if (*old_fd != -1)
		close(*old_fd);
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
		execute_pipe_cmd(tree, envp, status);
	}
	set_parent_signal();
	close(*old_fd);
	return (pid);
}

void	execute_pipe(t_tree **tree, t_envp *envp, int *status)
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
	free(pids);
}
