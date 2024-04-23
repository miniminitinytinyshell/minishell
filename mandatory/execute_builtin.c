/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:57:10 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/18 23:20:45 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

int	find_builtin(t_tree *tree)
{
	if (!tree)
		return (0);
	if (!tree->data)
		return (1);
	if (ft_strncmp(tree->data[0], "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(tree->data[0], "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(tree->data[0], "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(tree->data[0], "export", 7) == 0)
		return (1);
	else if (ft_strncmp(tree->data[0], "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(tree->data[0], "env", 4) == 0)
		return (1);
	else if (ft_strncmp(tree->data[0], "exit", 5) == 0)
		return (1);
	return (0);
}

void	proc_builtin(t_tree *tree, t_envp *envp, int *status)
{
	if (ft_strncmp(tree->data[0], "echo", 5) == 0)
		*status = builtin_echo(tree->data);
	else if (ft_strncmp(tree->data[0], "cd", 3) == 0)
		*status = builtin_cd(tree->data, envp);
	else if (ft_strncmp(tree->data[0], "pwd", 4) == 0)
		*status = builtin_pwd(tree->data, envp);
	else if (ft_strncmp(tree->data[0], "export", 7) == 0)
		*status = builtin_export(tree->data, envp);
	else if (ft_strncmp(tree->data[0], "unset", 6) == 0)
		*status = builtin_unset(tree->data, envp);
	else if (ft_strncmp(tree->data[0], "env", 4) == 0)
		*status = builtin_env(tree->data, envp);
	else if (ft_strncmp(tree->data[0], "exit", 5) == 0)
		*status = builtin_exit(tree->data);
}

void	execute_builtin(t_tree *tree, t_envp *envp, int *status)
{
	int	input;
	int	output;

	input = dup(STDIN_FILENO);
	output = dup(STDOUT_FILENO);
	if (tree->right->data)
		if (execute_rdr(tree->left, status))
			proc_builtin(tree->right, envp, status);
	dup2(input, STDIN_FILENO);
	dup2(output, STDOUT_FILENO);
	close(input);
	close(output);
}
