/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:41:40 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/12 15:35:42 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

int	error_export_option(char *opt)
{
	if (!opt)
		return (0);
	if (opt[0] == '-')
	{
		ft_putstr_fd("minishell: export: ", STDERR_FILENO);
		ft_putstr_fd("invalid option: ", STDERR_FILENO);
		ft_putendl_fd(opt, STDERR_FILENO);
		ft_putstr_fd("export: usage: ", STDERR_FILENO);
		ft_putstr_fd("export [name [=value] ...]", STDERR_FILENO);
		ft_putendl_fd(" or export", STDERR_FILENO);
		return (0);
	}
	return (1);
}

void	export_envp(char *arg, t_envp *envp)
{
	int		i;
	char	**temp;

	i = 0;
	temp = ft_calloc(envp->curr_cnt + 2, sizeof(char *));
	while (i < envp->curr_cnt)
	{
		temp[i] = ft_strdup(envp->data[i]);
		i++;
	}
	temp[i] = ft_strdup(arg);
	envp->data = free_tab(envp->data);
	envp->data = temp;
	envp->curr_cnt += 1;
	envp->max_cnt = envp->curr_cnt;
}

int	check_envp_arg(char *arg, t_envp *envp)
{
	int	j;

	j = 0;
	while (arg[j] && arg[j] != '=')
	{
		if (ft_isalnum(arg[j]) == 0 && arg[j] != '_')
			return (0);
		j++;
	}
	if (arg[j] == '=')
		export_envp(arg, envp);
	return (1);
}

int	builtin_export(char **args, t_envp *envp)
{
	int		i;
	int		check;

	i = 1;
	check = 0;
	if (!args[1])
		return (builtin_env(args, envp->data));
	else
	{
		if (error_export_option(args[1]))
		{
			while (args[i])
			{
				if (ft_isdigit(args[i][0]))
					check = error_not_vaild("export", args[i]);
				else
					if (check_envp_arg(args[i], envp) == 0)
						check = error_not_vaild("export", args[i]);
				i++;
			}
		}
		else
			check = 1;
	}
	return (check);
}
