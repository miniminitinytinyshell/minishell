/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:08:24 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/09 14:39:13 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

void	execute_rdr(t_tree *tree)
{
	int	file_in;
	int	file_out;

	if (!tree)
		return ;
	file_in = 0;
	file_out = 0;
	open_file(tree, &file_in, &file_out);
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
}

void	execute_cmd(t_tree *tree, t_envp *envp)
{
	int		check;
	char	*path;

	check = 0;
	if (!tree)
		return ;
	if (access(tree->data[0], O_RDONLY) == 0)
		path = ft_strdup(tree->data[0]);
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
	if (find_builtin(*tree))
		execute_builtin(*tree, envp, status);
	else
	{
		pid = fork();
		if (pid == -1)
			error_syscall();
		if (pid == 0)
		{
			set_child_signal();
			execute_rdr((*tree)->left);
			execute_cmd((*tree)->right, envp);
			exit(EXIT_FAILURE);
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
	*tree = free_tree(*tree);
}
