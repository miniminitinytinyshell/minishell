/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:41:40 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/12 14:39:04 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

int	error_unset(char *cmd)
{
	ft_putstr_fd("minishell: unset: ", STDERR_FILENO);
	ft_putstr_fd("not a valid identifier '", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
	return (1);
}

void	unset_envp(t_envp *envp, int idx)
{
	envp->data[idx] = free_null(envp->data[idx]);
	while (idx < envp->curr_cnt)
	{
		envp->data[idx] = envp->data[idx + 1];
		idx++;
	}
	envp->curr_cnt -= 1;
}

int	builtin_unset(char **args, t_envp *envp)
{
	int	i;
	int	idx;
	int	check;

	i = 1;
	check = 0;
	while (args[i])
	{
		idx = -1;
		if (ft_isdigit(args[i][0]))
			check = error_unset(args[i]);
		else
		{
			idx = get_envp_idx(args[i], envp);
			if (idx != -1)
				unset_envp(envp, idx);
		}
		i++;
	}
	return (check);
}
