/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:08:24 by jaeblee           #+#    #+#             */
/*   Updated: 2024/03/29 15:36:19 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

int	execute_cmd()
{
	
}

int	execute_std_cmd(t_tree **tree, char **envp, int *status)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error_fork();
	if (pid == 0)
	{
		
		execute_cmd();
	}
	else
		waitpid(pid, status, 0);
}

int	execute_cpd_cmd(t_tree **tree, char **envp, int *status)
{
	if ((*tree)->type == standard_cmd)
		execute_std_cmd(tree, envp, status);
	else if ((*tree)->type = compound_cmd)
	{
		if (ft_strncmp((*tree)->oper, "&&", 3) == 0)
		{
			execute_cpd_cmd((*tree)->left, envp, *status);
			if (*status == 0)
				execute_cpd_cmd((*tree)->right, envp, *status);
		}
		else if (ft_strncmp((*tree)->oper, "||", 3) == 0)
		{
			execute_cpd_cmd((*tree)->left, envp, *status);
			if (*status != 0)
				execute_cpd_cmd((*tree)->right, envp, *status);
		}
		else
			execute_pipe(tree, envp, status);
			// 오른쪽 트리가 STD인 경우 그냥 진행
			// CPD인 경우에 CPD의 왼쪽 트리만 pipe에 걸리게 작동
			// CPD의 오른쪽 트리는 다시 exec_cpd함수
	}
}

