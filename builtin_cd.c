/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:16:58 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/04/12 17:29:13 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

// static int	cd_getcwd_error(int flag)
// {
// 	if (flag == 0)
// 	{
// 		ft_putstr_fd("minishell: cd: getcwd: ", STDERR_FILENO);
// 		ft_putendl_fd(strerror(errno), STDERR_FILENO);
// 	}
// 	else
// 	{
// 		ft_putstr_fd("cd: error retrieving current directory: ", STDERR_FILENO);
// 		ft_putstr_fd("getcwd: cannot access parent directories: ", STDERR_FILENO);
// 		ft_putendl_fd("No such file or directory", STDERR_FILENO);
// 	}
// 	return (EXIT_FAILURE);
// }

int	cd_home_error(void)
{
	ft_putendl_fd("minishell: cd: HOME not set", STDERR_FILENO);
	return (EXIT_FAILURE);
}

int	cd_pwd_error(char *path)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putendl_fd(": No such file of directory", STDERR_FILENO);
	return (EXIT_FAILURE);
}

void	set_pwd(char *path, t_envp *envp)
{
	char	*tmp_path;
	char	*old_path;

	old_path = envp->pwd;
	swap_envp_data("OLDPWD", old_path, envp);
	if (*path != '/')
	{
		old_path = strjoin_char(old_path, '/');
		tmp_path = ft_strjoin(old_path, path);
	}
	else
	{
		free(old_path);
		tmp_path = ft_strdup(path);
	}
	if (!tmp_path)
		error_syscall();
	swap_envp_data("PWD", tmp_path, envp);
	envp->pwd = tmp_path;
}

// 우선 단순하게 문제 없는 상황에 대해서만 만들고,
// 상위디렉토리가 삭제되는 경우에는 다른 함수 호출하게 만들어보자...
int	builtin_cd(char **args, t_envp *envp)
{
	int		result;
	int		path_idx;
	char	*path;

	if (!args[1])
	{
		path_idx = get_envp_idx("HOME", envp);
		if (path_idx < 0)
			return (cd_home_error());
		path = ft_strchr(envp->data[path_idx], '=') + 1;
	}
	else
		path = args[1];
	result = chdir(path);
	if (result == 0)
		set_pwd(path, envp);
	else if (result < 0)
		return (cd_pwd_error(path));
	return (result);
}
