/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:57:10 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/04 15:16:23 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

void	restore_io(int input, int output)
{
	dup2(input, STDIN_FILENO);
	dup2(output, STDOUT_FILENO);
	close(input);
	close(output);
}

int	find_builtin(t_tree *tree, char **envp, int *status)
{
	int	input;
	int	output;

	input = dup(STDIN_FILENO);
	output = dup(STDOUT_FILENO);
	execute_rdr(tree->left);
	(void) envp;
	if (ft_strncmp(tree->data[0], "echo", 5) == 0)
		*status =  builtin_echo(tree->data);
	// else if (ft_strncmp(tree->data[0], "cd", 3) == 0)
	// 	*status = builtin_cd(tree->data, get_envp_list(envp));
	// else if (ft_strncmp(tree->data[0], "pwd", 4) == 0)
	// 	*status = builtin_pwd();
	// else if (ft_strncmp(tree->data[0], "export", 7) == 0)
	// 	*status = builtin_export();
	// else if (ft_strncmp(tree->data[0], "unset", 6) == 0)
	// 	*status = builtin_unset();
	// else if (ft_strncmp(tree->data[0], "env", 4) == 0)
	// 	*status = builtin_env();
	// else if (ft_strncmp(tree->data[0], "exit", 5) == 0)
	// 	*status = builtin_exit();
	else
		return (0);
	restore_io(input, output);
	return (1);
}
