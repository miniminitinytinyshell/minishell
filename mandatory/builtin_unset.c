/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:41:40 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/21 14:16:53 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

static int	unset_option_error(char *opt)
{
	if (!opt)
		return (1);
	if (opt[0] == '-')
	{
		ft_putstr_fd("mongshell: unset: ", STDERR_FILENO);
		ft_putstr_fd("invalid option: ", STDERR_FILENO);
		ft_putendl_fd(opt, STDERR_FILENO);
		ft_putstr_fd("unset: usage: unset [name ...]", STDERR_FILENO);
		return (0);
	}
	return (1);
}

static void	unset_envp(t_envp *envp, int idx)
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
	if (unset_option_error(args[1]))
	{
		while (args[i])
		{
			idx = -1;
			if (!ft_isalpha(args[i][0]) && args[i][0] != '_')
				check = error_not_valid("unset", args[i]);
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
