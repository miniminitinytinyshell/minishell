/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:16:58 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/04/09 20:22:37 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

static int	cd_getcwd_error(int flag)
{
	if (flag == 0)
	{
		ft_putstr_fd("minishell: cd: getcwd: ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd("cd: error retrieving current directory: ", STDERR_FILENO);
		ft_putstr_fd("getcwd: cannot access parent directories: ", STDERR_FILENO);
		ft_putendl_fd("No such file or directory", STDERR_FILENO);
	}
	return (EXIT_FAILURE);
}

void	set_pwd(char *path, char *old_path, t_envp *envp)
{
	char	*tmp_path;

	if (path[0] != '/')
		tmp_path = getcwd(NULL, 0);
	// tmp_path = getcwd(NULL, 0);
	printf("%s\n", tmp_path);
	printf("%s\n", path);
	swap_envp_data("PWD", path, envp);
	swap_envp_data("OLDPWD", old_path, envp);
}
// 우선 단순하게 문제 없는 상황에 대해서만 만들고,
// 상위디렉토리가 삭제되는 경우에는 다른 함수 호출하게 만들어보자...
int	builtin_cd(char **args, t_envp *envp)
{
	int		result;
	char	*path;
	char	*old_path;

	old_path = getenv("OLDPWD");
	if (!old_path)
		return (cd_getcwd_error(0));
	if (!args[1])
		path = getenv("HOME");
	else
		path = args[1];
	result = chdir(path);
	if (result == 0)
		set_pwd(path, old_path, envp);
	return (result);
}
