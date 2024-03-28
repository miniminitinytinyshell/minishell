/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:27:20 by jaeblee           #+#    #+#             */
/*   Updated: 2024/03/28 17:03:26 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

int	find_bulitin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	else
		return (0);
}

char	*word_join(char *str, char c)
{
	int		i;
	char	*word;

	i = 0;
	if (str)
	{
		word = (char *)malloc(sizeof(char) * (ft_strlen(str) + 2));
		while (str[i])
		{
			word[i] = str[i];
			i++;
		}
		free(str);
	}
	else
		word = (char *)malloc(sizeof(char) * 2);
	word[i] = c;
	word[i + 1] = '\0';
	return (word);
}

char	*find_env(char *origin, char *aim, char **envp)
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
				if (!origin)
					origin = ft_strdup("");
				result = ft_strjoin(origin, *envp + len + 1);
				break ;
			}
		}
		envp++;
	}
	if (!(*envp) && origin)
		result = ft_strdup(origin);
	return (result);
}

char	**get_path(char **envp)
{
	char	*temp;
	char	**path;

	path = NULL;
	temp = find_env("", "PATH", envp);
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
