/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:16:58 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/04/08 15:24:01 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

static int	cd_getcwd_error(void)
{
	ft_putstr_fd("minishell: cd: getcwd: ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
	return (EXIT_FAILURE);
}

// void	set_pwd_oldpwd(char *path, char *old_path, char **envp)
// {
// }

int	builtin_cd(char **args, t_envp *envp)
{
	int		result;
	char	*path;
	char	*old_path;

	old_path = getcwd(NULL, 0);
	if (!old_path)
		return (cd_getcwd_error());
	if (!args[1])
		path = getenv("HOME");
	else
		path = args[1];
	result = chdir(path);
	if (result == 0)
	{
		swap_envp_data("PWD", path, envp);
		swap_envp_data("OLDPWD", old_path, envp);
	}
	return (result);
}
