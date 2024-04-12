/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:16:58 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/04/12 18:51:40 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

int	cd_home_error(void)
{
	ft_putendl_fd("minishell: cd: HOME not set", STDERR_FILENO);
	return (EXIT_FAILURE);
}

int	cd_pwd_error(char *path)
{
	if (path)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putendl_fd(": No such file of directory", STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd("cd: error retrieving current directory: ", STDERR_FILENO);
		ft_putstr_fd("getcwd: ", STDERR_FILENO);
		ft_putstr_fd("cannot access parent directories: ", STDERR_FILENO);
		ft_putendl_fd("No such file or directory", STDERR_FILENO);
	}
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
}

char	*set_rel_path(char *pwd, char *target)
{
	char	*rel_path;
	char	*tmp;
	int		pwd_len;

	pwd_len = ft_strlen(pwd);
	if (pwd[pwd_len - 1] == '/')
		tmp = ft_strdup(pwd);
	else
		tmp = ft_strjoin(pwd, "/");
	rel_path = ft_strjoin(tmp, target);
	free(tmp);
	return (rel_path);
}

int	builtin_cd(char **args, t_envp *envp)
{
	int		result;
	char	*path;

	if (!args[1])
		path = ft_strchr(envp->data[get_envp_idx("HOME", envp)], '=') + 1;
	else
	{
		path = set_rel_path(envp->pwd, args[1]);
		if (access(path, F_OK) < 0)
			path = ft_strdup(args[1]);
	}
	result = chdir(path);
	if (result == 0)
		set_pwd(path, envp);
	else
		cd_pwd_error(path);
	free(path);
	return (result);
}
