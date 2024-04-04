/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:16:58 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/04/04 14:54:35 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

char	*get_home_dir(t_env *env_list)
{
	char	*path;

	path = NULL;
	while (env_list)
	{
		if (ft_strncmp(env_list->key, "HOME", 5) == 0)
			break ;
		env_list = env_list->next;
	}
	path = env_list->value;
	return (path);
}

int	builtin_cd(char **args, t_env *env_list)
{
	int		result;
	char	*path;

	if (args[1] == NULL)
		path = get_home_dir(env_list);
	else
		path = args[1];
	result = chdir(path);
	if (result < 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(args[0], STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
	}
	return (result);
}
