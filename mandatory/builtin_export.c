/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:41:40 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/23 16:32:15 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

static int	export_option_error(char *opt)
{
	ft_putstr_fd("mongshell: export: ", STDERR_FILENO);
	ft_putstr_fd("invalid option: ", STDERR_FILENO);
	ft_putchar_fd(opt[0], STDERR_FILENO);
	ft_putchar_fd(opt[1], STDERR_FILENO);
	ft_putendl_fd("", STDERR_FILENO);
	ft_putstr_fd("export: usage: ", STDERR_FILENO);
	ft_putstr_fd("export [name[=value] ...]", STDERR_FILENO);
	ft_putendl_fd(" or export", STDERR_FILENO);
	return (1);
}

int	declare_env(t_envp *envp)
{
	int		i;
	int		j;
	char	**data;

	i = 0;
	data = envp->data;
	while (data[i])
	{
		j = 0;
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		while (data[i][j] && data[i][j] != '=')
			ft_putchar_fd(data[i][j++], STDOUT_FILENO);
		if (data[i][j] == '=')
		{
			ft_putchar_fd(data[i][j], STDOUT_FILENO);
			ft_putchar_fd('"', STDOUT_FILENO);
			ft_putstr_fd(&data[i][j + 1], STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
		i++;
	}
	return (0);
}

char	*check_env_key(char *arg)
{
	int		len;
	char	*key;

	len = 1;
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (NULL);
	while (arg[len])
	{
		if (arg[len] == '=')
			break ;
		if (!ft_isalnum(arg[len]) && arg[len] != '_')
			return (NULL);
		len++;
	}
	key = ft_calloc(len + 1, sizeof(char));
	if (!key)
		error_syscall();
	ft_strlcpy(key, arg, len + 1);
	return (key);
}

int	set_new_env(char *arg, t_envp *envp)
{
	int		i;
	char	**temp;

	if (envp->curr_cnt < envp->max_cnt)
		envp->data[envp->curr_cnt] = ft_strdup(arg);
	else
	{
		temp = ft_calloc(envp->max_cnt * 2, sizeof(char *));
		if (!temp)
			error_syscall();
		i = 0;
		while (i < envp->curr_cnt && envp->data[i])
		{
			temp[i] = ft_strdup(envp->data[i]);
			i++;
		}
		envp->max_cnt *= 2;
		temp[i] = ft_strdup(arg);
		free_tab(envp->data);
		envp->data = temp;
	}
	if (!envp->data[envp->curr_cnt])
		error_syscall();
	envp->curr_cnt += 1;
	return (0);
}

int	builtin_export(char **args, t_envp *envp)
{
	int		i;
	int		result;
	char	*key;

	i = 1;
	result = 0;
	if (!args[1])
		return (declare_env(envp));
	if (args[1][0] == '-' && ft_strlen(args[1]) > 1)
		return (export_option_error(args[1]));
	while (args[i])
	{
		key = check_env_key(args[i]);
		if (!key)
			result = error_not_valid("export", args[i]);
		else
		{
			if (swap_envp_data(key, ft_strchr(args[i], '='), envp))
				set_new_env(args[i], envp);
			key = free_null(key);
		}
		i++;
	}
	return (result);
}
