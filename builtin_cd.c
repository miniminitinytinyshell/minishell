/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:16:58 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/04/04 15:35:07 by hyeunkim         ###   ########.fr       */
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

int	change_pwd(char *old_path, t_env *env_list)
{
	t_env	*temp;

	temp = find_env(env_list, "PWD");
	free(temp->value);
	temp->value = getcwd(NULL, 0);
	if (!temp->value)
		return (-1);
	temp = find_env(env_list, "OLDPWD");
	free(temp->value);
	temp->value = old_path;
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
		path = get_home_dir(env_list);
	else
		path = args[1];
	result = chdir(path);
	if (result < 0)
		error_cd(args[1]);
	else
	{
		if (change_pwd(old_path, env_list) < 0)
			error_malloc();
	}
	return (result);
}
