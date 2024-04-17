/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:29:36 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/16 20:42:54 by hyeunkim         ###   ########.fr       */
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

static pid_t	proc_fork(t_tree *tree, t_envp *envp, int *status)
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
		close(fd[1]);
		execute_cpd_cmd(&tree->left, envp, status);
		exit(*status);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	return (pid);
}

static pid_t	last_fork(t_tree *tree, t_envp *envp, int *status)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error_syscall();
	if (pid == 0)
	{
		execute_cpd_cmd(&tree, envp, status);
		exit(*status);
	}
	else
		close(STDIN_FILENO);
	return (pid);
}

void	process_pipe(t_tree **tree, t_envp *envp, int *status)
{
	int		i;
	int		count;
	pid_t	*pids;
	t_tree	*temp;

	i = 0;
	temp = *tree;
	count = count_pipe(*tree);
	pids = ft_calloc(count + 1, sizeof(pid_t));
	while (i < count)
	{
		pids[i] = proc_fork(temp, envp, status);
		temp = temp->right;
		i++;
	}
	pids[i] = last_fork(temp, envp, status);
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
	int	input;

	input = dup(STDIN_FILENO);
	// signal(SIGPIPE, SIG_IGN);
	process_pipe(tree, envp, status);
	dup2(input, STDIN_FILENO);
	close(input);
}
