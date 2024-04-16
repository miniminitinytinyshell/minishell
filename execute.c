/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:08:24 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/16 18:21:19 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

extern int	g_signum;

int	execute_rdr(t_tree *tree, int *status)
{
	int	file_in;
	int	file_out;

	if (!tree)
		return (1);
	file_in = 0;
	file_out = 0;
	*status = open_file(tree, &file_in, &file_out);
	if (file_in > 0)
	{
		if (dup2(file_in, STDIN_FILENO) == -1)
			error_syscall();
		close(file_in);
	}
	if (file_out > 0)
	{
		if (dup2(file_out, STDOUT_FILENO) == -1)
			error_syscall();
		close(file_out);
	}
	if (*status != 0)
		return (0);
	return (1);
}

void	execute_cmd(t_tree *tree, t_envp *envp)
{
	char	*path;

	path = NULL;
	set_child_signal();
	if (!tree)
		return ;
	if (tree->data[0][0] == '\0')
		path = NULL;
	else if (access(tree->data[0], F_OK) == 0)
		path = check_file(tree->data[0]);
	else
		path = get_cmd_path(tree->data[0], get_path(envp));
	if (!path)
		error_cmd_not_found(tree->data[0]);
	if (execve(path, tree->data, envp->data) == -1)
		error_syscall();
}

void	execute_std_cmd(t_tree **tree, t_envp *envp, int *status)
{
	pid_t	pid;

	expand_tree(tree, envp->data, *status);
	if (find_builtin((*tree)->right))
		execute_builtin(*tree, envp, status);
	else
	{
		pid = fork();
		if (pid == -1)
			error_syscall();
		if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			if (execute_rdr((*tree)->left, status))
				execute_cmd((*tree)->right, envp);
			exit(*status);
		}
		else
		{
			set_parent_signal();
			waitpid(pid, status, 0);
			set_status(status);
		}
	}
}

void	execute_cpd_cmd(t_tree **tree, t_envp *envp, int *status)
{
	if ((*tree)->type == standard_cmd)
		execute_std_cmd(tree, envp, status);
	else if ((*tree)->type == compound_cmd)
	{
		if (ft_strncmp((*tree)->oper, "&&", 3) == 0)
		{
			execute_cpd_cmd(&(*tree)->left, envp, status);
			if (*status == 0)
				execute_cpd_cmd(&(*tree)->right, envp, status);
		}
		else if (ft_strncmp((*tree)->oper, "||", 3) == 0)
		{
			execute_cpd_cmd(&(*tree)->left, envp, status);
			if (*status != 0)
				execute_cpd_cmd(&(*tree)->right, envp, status);
		}
		else
			execute_pipe(tree, envp, status);
	}
}

void	execute_tree(t_tree **tree, t_envp *envp, int *status)
{
	int	file_name;

	file_name = 1;
	create_heredoc(tree, &file_name, envp);
	if (g_signum != SIGINT)
		execute_cpd_cmd(tree, envp, status);
	if (file_name > 1)
		delete_heredoc(tree);
}
