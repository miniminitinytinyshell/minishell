/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:16:58 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/04/07 11:04:18 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

int	builtin_cd(char **args, char **envp)
{
	int		result;
	char	*old_path;
	char	*path;

	old_path = getcwd(NULL, 0);
	if (!(args[1]))
		result = cd_to_home(envp);
	else
		result = cd_to_arg(args);
	if (result < 0)
		return (error_cd(path));
	// else
	// {
	// 	if (change_pwd(old_path, envp, env_list) < 0)
	// 		error_syscall();
	// }
	return (result);
}
