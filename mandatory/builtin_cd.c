/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:16:58 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/04/21 12:06:19 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

int	cd_home_error(void)
{
	ft_putendl_fd("mongshell: cd: HOME not set", STDERR_FILENO);
	return (EXIT_FAILURE);
}

int	cd_pwd_error(char *path)
{
	if (path)
		error_with_str(path, 0);
	else
	{
		ft_putstr_fd("cd: error retrieving current directory: ", STDERR_FILENO);
		ft_putstr_fd("getcwd: ", STDERR_FILENO);
		ft_putstr_fd("cannot access parent directories: ", STDERR_FILENO);
		ft_putendl_fd("No such file or directory", STDERR_FILENO);
	}
	path = free_null(path);
	return (EXIT_FAILURE);
}

void	set_pwd(char *path, t_envp *envp)
{
	char	*tmp_path;
	char	*old_path;

	old_path = envp->pwd;
	swap_envp_data("OLDPWD", old_path, envp);
	tmp_path = getcwd(NULL, 0);
	if (!tmp_path)
	{
		cd_pwd_error(NULL);
		if (old_path[ft_strlen(old_path) - 1] != '/')
			old_path = strjoin_char(old_path, '/');
		tmp_path = ft_strjoin(old_path, path);
	}
	swap_envp_data("PWD", tmp_path, envp);
	envp->pwd = tmp_path;
	free(old_path);
	path = free_null(path);
}

char	*set_path(char *pwd, char *target)
{
	char	*path;
	char	*tmp;
	int		pwd_len;

	if (pwd[0] == '/')
		path = ft_strdup(target);
	else
	{
		pwd_len = ft_strlen(pwd);
		if (pwd[pwd_len - 1] == '/')
			tmp = ft_strdup(pwd);
		else
			tmp = ft_strjoin(pwd, "/");
		path = ft_strjoin(tmp, target);
		free(tmp);
		if (access(path, F_OK) < 0)
		{
			free(path);
			path = ft_strdup(target);
		}
	}
	return (path);
}

int	builtin_cd(char **args, t_envp *envp)
{
	int		result;
	int		idx;
	char	*path;

	if (!args[1])
	{
		idx = get_envp_idx("HOME", envp);
		if (idx < 0)
			return (cd_home_error());
		path = ft_strdup(ft_strchr(envp->data[idx], '=') + 1);
	}
	else
		path = set_path(envp->pwd, args[1]);
	if (!path)
		error_syscall();
	result = chdir(path);
	if (result == 0)
		set_pwd(path, envp);
	else
		result = cd_pwd_error(path);
	return (result);
}
