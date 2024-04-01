/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:27:20 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/01 20:21:58 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

// int	find_builtin(t_tree *tree, char **envp, int *status)
// {
// 	if (ft_strncmp(tree->data[0], "echo", 5) == 0)
// 		builtin_echo(tree->data, envp, status);
	// else if (ft_strncmp(tree->data[0], "cd", 3) == 0)
	// 	builtin_cd();
	// else if (ft_strncmp(tree->data[0], "pwd", 4) == 0)
	// 	builtin_pwd();
	// else if (ft_strncmp(tree->data[0], "export", 7) == 0)
	// 	builtin_export();
	// else if (ft_strncmp(tree->data[0], "unset", 6) == 0)
	// 	builtin_unset();
	// else if (ft_strncmp(tree->data[0], "env", 4) == 0)
	// 	builtin_env();
	// else if (ft_strncmp(tree->data[0], "exit", 5) == 0)
	// 	builtin_exit();
	// else
	// 	return (0);
// 	return (1);
// }

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
