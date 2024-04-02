/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:08:24 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/02 15:06:13 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

void	execute_rdr(t_tree *tree)
{
	int	file_in;
	int	file_out;

	file_in = 0;
	file_out = 0;
	if (!tree)
		return ;
	if (ft_strncmp(tree->left->data[0], "<", 2) == 0)
		file_in = open(tree->left->data[1], O_RDONLY, 0644);
	else if (ft_strncmp(tree->left->data[0], ">", 2) == 0)
		file_out = open(tree->left->data[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (ft_strncmp(tree->left->data[0], ">>", 3) == 0)
		file_out = open(tree->left->data[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// else
	// 	hear_doc();
	if (file_in > 0)
		dup2(file_in, STDIN_FILENO);
	else if (file_in < 0)
		exit(EXIT_FAILURE);
	if (file_out)
		dup2(file_out, STDOUT_FILENO);
	execute_rdr(tree->right);
}

void	execute_cmd(t_tree *tree, char **envp)
{
	char	*path;

	if (!tree)
		return ;
	if (find_builtin(tree, envp) == 0)
	{
		if (access(tree->data[0], O_RDONLY) == 0)
			path = ft_strdup(tree->data[0]);
		else
			path = get_cmd_path(tree->data[0], get_path(envp));
		if (!path)
			error_cmd_not_found(tree->data[0]);
		if (execve(path, tree->data, envp) == -1)
			exit(EXIT_FAILURE);
	}
	// if (access(tree->data[0], O_RDONLY) == 0)
	// 	path = ft_strdup(tree->data[0]);
	// else
	// 	path = get_cmd_path(tree->data[0], get_path(envp));
	// if (!path)
	// 	error_cmd_not_found(tree->data[0]);
	// if (execve(path, tree->data, envp) == -1)
	// 	exit(EXIT_FAILURE);
}

void	execute_std_cmd(t_tree **tree, char **envp, int *status)
{
	pid_t	pid;

	expand_tree(tree, envp, *status);
	pid = fork();
	if (pid == -1)
		error_fork();
	if (pid == 0)
	{
		execute_rdr((*tree)->left);
		execute_cmd((*tree)->right, envp);
		exit(EXIT_SUCCESS);
	}
	else
	{
		waitpid(pid, status, 0);
		*status = WEXITSTATUS(*status);
	}
}

void	execute_pipe(t_tree **tree, char **envp, int *status)
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
}

int	execute_cpd_cmd(t_tree **tree, char **envp, int *status)
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
	return (1);
}

