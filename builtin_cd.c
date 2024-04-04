/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:16:58 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/04/04 18:47:29 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

int	change_pwd(char *old_path, char **envp, t_env *env_list)
{
	t_env	*temp_node;
	int		idx;

	temp_node = find_env_node(env_list, "PWD");
	free(temp_node->value);
	temp_node->value = getcwd(NULL, 0);
	idx = find_env_idx("PWD", env_list);
	free(envp[idx]);
	envp[idx] = envp_join(temp_node);
	if (!temp_node->value)
		return (-1);
	temp_node = find_env_node(env_list, "OLDPWD");
	free(temp_node->value);
	temp_node->value = old_path;
	idx = find_env_idx("OLDPWD", env_list);
	free(envp[idx]);
	envp[idx] = envp_join(temp_node);
	return (0);
}

int	builtin_cd(char **args, char **envp)
{
	int		result;
	t_env	*env_list;
	char	*old_path;
	char	*path;

	env_list = get_envp_list(envp);
	old_path = getcwd(NULL, 0);
	if (args[1] == NULL)
		path = getenv("HOME");
	else
		path = args[1];
	result = chdir(path);
	if (result < 0)
		error_cd(args[1]);
	else
	{
		if (change_pwd(old_path, envp, env_list) < 0)
			error_malloc();
	}
	return (result);
}
