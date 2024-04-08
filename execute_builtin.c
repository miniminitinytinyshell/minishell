/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:57:10 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/08 13:53:07 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

void	execute_builtin(t_tree *tree, t_envp *envp, int *status)
{
	int	input;
	int	output;

	input = dup(STDIN_FILENO);
	output = dup(STDOUT_FILENO);
	execute_rdr(tree->left);
	if (ft_strncmp(tree->right->data[0], "echo", 5) == 0)
		*status =  builtin_echo(tree->right->data);
	else if (ft_strncmp(tree->right->data[0], "cd", 3) == 0)
		*status = builtin_cd(tree->right->data, envp);
	else if (ft_strncmp(tree->right->data[0], "pwd", 4) == 0)
		*status = builtin_pwd(tree->right->data);
	// else if (ft_strncmp(tree->right->data[0], "export", 7) == 0)
	// 	*status = builtin_export();
	// else if (ft_strncmp(tree->right->data[0], "unset", 6) == 0)
	// 	*status = builtin_unset();
	else if (ft_strncmp(tree->right->data[0], "env", 4) == 0)
		*status = builtin_env(tree->right->data, envp->data);
	// else if (ft_strncmp(tree->right->data[0], "exit", 5) == 0)
	// 	*status = builtin_exit();
	dup2(input, STDIN_FILENO);
	dup2(output, STDOUT_FILENO);
	close(input);
	close(output);
}

int	find_builtin(t_tree *tree)
{
	if (ft_strncmp(tree->right->data[0], "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(tree->right->data[0], "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(tree->right->data[0], "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(tree->right->data[0], "export", 7) == 0)
		return (1);
	else if (ft_strncmp(tree->right->data[0], "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(tree->right->data[0], "env", 4) == 0)
		return (1);
	else if (ft_strncmp(tree->right->data[0], "exit", 5) == 0)
		return (1);
	return (0);
}
