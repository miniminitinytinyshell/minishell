/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:41:40 by jaeblee           #+#    #+#             */
/*   Updated: 2024/05/03 15:29:11 by hyeunkim         ###   ########.fr       */
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

static void	unset_envp(t_envp *envp, char *arg)
{
	int	idx;

	idx = get_envp_idx(arg, envp);
	if (ft_strncmp(arg, "PATH", 5) == 0)
		envp->path = free_null(envp->path);
	if (idx < 0)
		return ;
	envp->data[idx] = free_null(envp->data[idx]);
	while (idx < envp->curr_cnt)
	{
		envp->data[idx] = envp->data[idx + 1];
		idx++;
	}
	envp->curr_cnt -= 1;
}

static int	check_unset(char *arg)
{
	int	i;

	i = 0;
	if (!ft_isalpha(arg[i]) && arg[i] != '_')
		return (1);
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int	builtin_unset(char **args, t_envp *envp)
{
	int	i;
	int	check;

	i = 1;
	check = 0;
	if (unset_option_error(args[1]))
	{
		while (args[i])
		{
			if (check_unset(args[i]))
				check = error_not_valid("unset", args[i]);
			else
				unset_envp(envp, args[i]);
			i++;
		}
	}
	else
		check = 1;
	return (check);
}
