/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:16:58 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/04/08 13:28:46 by hyeunkim         ###   ########.fr       */
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

int	builtin_cd(char **args, char **envp)
{
	int		result;
	char	*path;
	char	*old_path;

	old_path = getcwd(NULL, 0);
	if (!old_path)
		return (cd_get_cwd_error());
	if (!args[0])
		path = getenv("HOME");
	else
		path = ft_strdup(args[1]);
	if (!path)
	return (result);
}
