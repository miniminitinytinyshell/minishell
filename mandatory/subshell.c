/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:36:21 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/17 18:39:55 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

void	proc_subshell(t_tree **tree, t_envp *envp, int *status)
{
	char	**cmds;

	set_child_signal();
	cmds = table_join(NULL, ft_strdup("./minishell"));
	for (int i = 0; (*tree)->data[i]; i++)
		cmds = table_join(cmds, (*tree)->data[i]);
	execve("minishell", cmds, envp->data);
}

void	execute_subshell(t_tree **tree, t_envp *envp, int *status)
{
	pid_t	pid;


	pid = fork();
	if (pid == -1)
		error_syscall();
	if (pid == 0)
		proc_subshell(tree, envp, status);
	else
	{
		set_parent_signal();
		waitpid(pid, status, 0);
		set_status(status);
	}
}
