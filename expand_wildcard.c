/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:22:39 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/08 15:22:38 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

static void	extract_path(char *str, char **path)
{
	int	i;

	i = ft_strlen(str);
	while (i > 0 && str[i - 1] != '/')
		i--;
	if (i == 0)
		path[0] = ft_calloc(3, sizeof(char));
	else
		path[0] = ft_calloc(i + 1, sizeof(char));
	path[1] = ft_calloc(ft_strlen(str) - i + 1, sizeof(char));
	if (!path[0] || !path[1])
		error_syscall();
	if (i == 0)
		ft_strlcpy(path[0], "./", 3);
	else
		ft_strlcpy(path[0], str, i + 1);
	ft_strlcpy(path[1], str + i, ft_strlen(str) - i + 1);
}

static int	match(char *pattern, char *str)
{
	while (*pattern)
	{
		if (*pattern == '*')
		{
			while (*str)
			{
				if (match(pattern + 1, str))
					return (1);
				str++;
			}
			return (match(pattern + 1, str));
		}
		else if (*pattern != '?' && *pattern != *str)
			return (0);
		pattern++;
		str++;
	}
	return (!(*str));
}

void	add_wildcard_data(char ***data, char **path, DIR *dir)
{
	struct dirent	*file;

	while (1)
	{
		file = readdir(dir);
		if (!file)
			break ;
		if (file->d_name[0] != '.' && match(path[1], file->d_name))
		{
			if (ft_strncmp(path[0], "./", 3) == 0)
				*data = table_join(*data, ft_strdup(file->d_name));
			else
				*data = table_join(*data, ft_strjoin(path[0], file->d_name));
		}
	}
}

void	expand_wildcard(t_tree **tree, int i)
{
	DIR				*dir;
	char			**path;
	char			**data;

	path = ft_calloc(3, sizeof(char *));
	if (!path)
		error_syscall();
	extract_path((*tree)->data[i], path);
	dir = opendir(path[0]);
	if (!dir)
		error_syscall();
	data = table_dup((*tree)->data, i);
	add_wildcard_data(&data, path, dir);
	closedir(dir);
	while ((*tree)->data[++i])
		data = table_join(data, ft_strdup((*tree)->data[i]));
	free_tab((*tree)->data);
	path = free_tab(path);
	(*tree)->data = data;
}
