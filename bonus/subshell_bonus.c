/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:36:21 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/17 19:31:25 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_bonus.h"
#include "function_bonus.h"

void	proc_subshell(t_tree **tree, t_envp *envp)
{
	int		i;
	char	**cmds;

	i = 0;
	set_child_signal();
	cmds = table_join(NULL, ft_strdup("./minishell"));
	while ((*tree)->data[i])
	{
		cmds = table_join(cmds, (*tree)->data[i]);
		i++;
	}
	execve("minishell", cmds, envp->data);
}

void	execute_subshell(t_tree **tree, t_envp *envp, int *status)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error_syscall();
	if (pid == 0)
		proc_subshell(tree, envp);
	else
	{
		set_parent_signal();
		waitpid(pid, status, 0);
		set_status(status);
	}
}
