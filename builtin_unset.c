/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:41:40 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/17 14:18:45 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

int	error_unset_option(char *opt)
{
	if (!opt)
		return (1);
	if (opt[0] == '-')
	{
		ft_putstr_fd("mongshell🐶: unset: ", STDERR_FILENO);
		ft_putstr_fd("invalid option: ", STDERR_FILENO);
		ft_putendl_fd(opt, STDERR_FILENO);
		ft_putstr_fd("unset: usage: unset [name ...]", STDERR_FILENO);
		return (0);
	}
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
	if (error_unset_option(args[1]))
	{
		while (args[i])
		{
			idx = -1;
			if (ft_isdigit(args[i][0]))
				check = error_not_vaild("unset", args[i]);
			else
			{
				idx = get_envp_idx(args[i], envp);
				if (idx != -1)
					unset_envp(envp, idx);
			}
			i++;
		}
	}
	else
		check = 1;
	return (check);
}
