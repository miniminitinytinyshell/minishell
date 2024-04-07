/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:08:24 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/07 18:34:41 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

void	open_file(t_tree *tree, int *file_in, int *file_out)
{
	if (!tree)
		return ;
	if (ft_strncmp(tree->left->data[0], "<", 1) == 0)
	{
		if (*file_in != 0)
			*file_in = close(*file_in);
		if (ft_strncmp(tree->left->data[0], "<", 2) == 0)
			*file_in = open(tree->left->data[1], O_RDONLY, 0644);
		else
			here_doc(tree->left->data[1], file_in);
	}
	else
	{
		if (*file_out != 0)
			*file_out = close (*file_out);
		if (ft_strncmp(tree->left->data[0], ">", 2) == 0)
			*file_out = open(tree->left->data[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			*file_out = open(tree->left->data[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	if (*file_in < 0)
		error_no_file(tree->left->data[1]);
	open_file(tree->right, file_in, file_out);
}

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
		dup2(file_in, STDIN_FILENO);
	if (file_out > 0)
		dup2(file_out, STDOUT_FILENO);
	close(file_in);
	close(file_out);
}

void	execute_cmd(t_tree *tree, char **envp)
{
	char	*path;

	if (!tree)
		return ;
	if (access(tree->data[0], O_RDONLY) == 0)
		path = ft_strdup(tree->data[0]);
	else
		path = get_cmd_path(tree->data[0], get_path(envp));
	if (!path)
		error_cmd_not_found(tree->data[0]);
	if (execve(path, tree->data, envp) == -1)
		exit(EXIT_FAILURE);
}

void	execute_std_cmd(t_tree **tree, char **envp, int *status)
{
	pid_t	pid;

	expand_tree(tree, envp, *status);
	if (find_builtin(*tree))
		execute_builtin(*tree, envp, status);
	else
	{
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
}

void	execute_cpd_cmd(t_tree **tree, char **envp, int *status)
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
