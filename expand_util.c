/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:27:20 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/04 15:40:36 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

char	*find_env(char *aim, char **envp)
{
	int		len;
	char	*result;

	len = ft_strlen(aim);
	result = NULL;
	while (*envp)
	{
		if (ft_strncmp(aim, *envp, len) == 0)
		{
			if (*(*envp + len) == '=')
			{
				result = ft_strdup(*envp + len + 1);
				break ;
			}
		}
		envp++;
	}
	return (result);
}

char	**get_path(char **envp)
{
	char	*temp;
	char	**path;

	path = NULL;
	temp = find_env("PATH", envp);
	if (temp)
	{
		path = ft_split(temp, ':');
		free(temp);
	}
	return (path);
}

char	*get_cmd_path(char *cmd, char **path)
{
	int		i;
	int		check;
	char	*temp_cmd;
	char	*result;

	i = 0;
	temp_cmd = ft_strjoin("/", cmd);
	while (path[i])
	{
		result = ft_strjoin(path[i++], temp_cmd);
		check = access(result, F_OK);
		if (check == 0)
		{
			free_tab(path);
			free(temp_cmd);
			return (result);
		}
		close(check);
		free(result);
	}
	free_tab(path);
	free(temp_cmd);
	return (NULL);
}
