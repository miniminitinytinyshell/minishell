/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:27:20 by jaeblee           #+#    #+#             */
/*   Updated: 2024/03/27 13:32:21 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

char	**free_tab(char **temp)
{
	int	i;

	i = 0;
	while (temp[i])
	{
		free(temp[i]);
		temp[i] = NULL;
		i++;
	}
	free(temp);
	temp = NULL;
	return (temp);
}

char	**get_path(char **envp)
{
	char	*temp;
	char	**path;

	temp = NULL;
	path = NULL;
	while (*envp)
	{
		if (ft_strncmp("PATH", *envp, 4) == 0)
			temp = ft_strdup(*envp + 5);
		envp++;
	}
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
			free(cmd);
			return (result);
		}
		close(check);
		free(result);
	}
	free_tab(path);
	free(temp_cmd);
	free(cmd);
	return (NULL);
}
