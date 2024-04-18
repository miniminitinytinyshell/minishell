/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:41:40 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/18 23:28:31 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

int	export_option_error(char *opt)
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
	int		idx;
	int		char_idx;
	char	**data;

	idx = 0;
	data = envp->data;
	while (data[idx])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		char_idx = 0;
		while (data[idx][char_idx] != '=')
		{
			ft_putchar_fd(data[idx][char_idx], STDOUT_FILENO);
			char_idx++;
		}
		ft_putchar_fd(data[idx][char_idx], STDOUT_FILENO);
		ft_putchar_fd('"', STDOUT_FILENO);
		ft_putstr_fd(data[idx] + char_idx + 1, STDOUT_FILENO);
		ft_putendl_fd("\"", STDOUT_FILENO);
		idx++;
	}
	return (0);
}

int	check_env_key(char *str)
{
	int	len;

	len = 0;
	if (!ft_strchr(str, '=') || ft_isdigit(str[len]) || str[len] == '_')
		return (-1);
	len++;
	while (str[len])
	{
		if (str[len] == '=')
			break ;
		if (ft_isalnum(str[len]) == 0 && str[len] != '_')
			return (-1);
		len++;
	}
	return (len);
}

int	set_new_env(char *arg, t_envp *envp)
{
	int		idx;
	char	**tmp;


	if (envp->curr_cnt < envp->max_cnt)
	{
		tmp = ft_calloc(envp->max_cnt, sizeof(char *));
		if (!tmp)
			error_syscall();
		idx = 0;
		while (idx < envp->curr_cnt)
		{
			tmp[idx] = ft_strdup(envp->data[idx]);
			idx++;
		}
		tmp[idx] = ft_strdup(arg);
		free_tab(envp->data);
		envp->data = tmp;
		envp->curr_cnt += 1;
	}
	else
	{
		tmp = ft_calloc(envp->max_cnt * 2, sizeof(char *));
		if (!tmp)
			error_syscall();
		idx = 0;
		while (idx < envp->max_cnt && envp->data[idx])
		{
			tmp[idx] = ft_strdup(envp->data[idx]);
			idx++;
		}
		tmp[idx] = ft_strdup(arg);
		free_tab(envp->data);
		envp->data = tmp;
		envp->curr_cnt += 1;
		envp->max_cnt *= 2;
	}
	return (0);
}

int	builtin_export(char **args, t_envp *envp)
{
	int		i;
	int		len;
	int		result;
	char	*key;

	if (!args[1])
		return (declare_env(envp));
	if (args[1] && args[1][0] == '-' && ft_strlen(args[1]) > 1)
		return (export_option_error(args[1]));
	i = 1;
	while (args[i])
	{
		len = check_env_key(args[i]);
		if (len < 0)
			return (error_not_valid("export", args[i]));
		key = ft_calloc(len + 1, sizeof(char));
		if (!key)
			error_syscall();
		ft_strlcpy(key, args[i], len + 1);
		if (swap_envp_data(key, ft_strchr(args[i], '=') + 1, envp) < 0)
			result = set_new_env(args[i], envp);
		key = free_null(key);
		i++;
	}
	return (result);
}
