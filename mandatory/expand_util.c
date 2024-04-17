/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:27:20 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/17 16:03:43 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

void	expand_quote(char c, char *quote, char **result)
{
	if (*quote == 0)
		*quote = c;
	else if (*quote == c)
		*quote = 0;
	else
		*result = strjoin_char(*result, c);
}

char	*find_env(char *aim, char **envp)
{
	int		len;
	char	*result;

	len = ft_strlen(aim);
	result = NULL;
	if (!envp)
		return (result);
	while (*envp)
	{
		if (ft_strncmp(aim, *envp, len) == 0)
		{
			if (*(*envp + len) == '=')
			{
				result = ft_strdup(*envp + len + 1);
				if (!result)
					error_syscall();
				break ;
			}
		}
		envp++;
	}
	return (result);
}

char	**get_path(t_envp *envp)
{
	char	*temp;
	char	**path;

	path = NULL;
	temp = find_env("PATH", envp->data);
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
	if (!path)
		exit(error_with_str(cmd, CMD_NFOUND));
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
