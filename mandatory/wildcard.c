/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:22:39 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/20 05:01:55 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

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

static char	*get_name(char **path, char *name)
{
	char		*data;
	struct stat	file_stat;

	if (ft_strncmp(path[0], ".", 2) == 0)
		data = ft_strdup(name);
	else
		data = ft_strjoin(path[0], name);
	if (path[2])
	{
		if (stat(data, &file_stat) == 0)
		{
			if (S_ISDIR(file_stat.st_mode))
			{
				data = strjoin_free(data, strdup(path[2]));
				if (access(data, F_OK) != 0)
					data = free_null(data);
			}
			else
				data = free_null(data);
		}
		else
			error_syscall();
	}
	return (data);
}

static int	add_wildcard_data(char ***data, char **path, DIR *dir)
{
	int				cnt;
	char			*temp;
	struct dirent	*file;

	cnt = 0;
	while (1)
	{
		file = readdir(dir);
		if (!file)
			break ;
		if ((path[1][0] == '.' && match(path[1], file->d_name)) || \
			(file->d_name[0] != '.' && match(path[1], file->d_name)))
		{
			temp = get_name(path, file->d_name);
			if (temp)
			{
				*data = table_join(*data, temp);
				cnt++;
			}
		}
	}
	if (cnt == 0)
		return (1);
	return (0);
}

static char	**add_remain_data(t_tree **tree, char **data, int i)
{
	int	idx;

	idx = i + 1;
	while ((*tree)->data[idx])
	{
		data = table_join(data, ft_strdup((*tree)->data[idx]));
		idx++;
	}
	return (data);
}

void	expand_wildcard(t_tree **tree, int i)
{
	DIR				*dir;
	char			**path;
	char			**data;

	path = ft_calloc(4, sizeof(char *));
	if (!path)
		error_syscall();
	if (extract_path((*tree)->data[i], path))
		return ;
	dir = opendir(path[0]);
	if (!dir)
	{
		free_tab(path);
		return ;
	}
	data = table_dup((*tree)->data, i);
	if (add_wildcard_data(&data, path, dir))
		data = table_join(data, ft_strdup((*tree)->data[i]));
	closedir(dir);
	data = add_remain_data(tree, data, i);
	free_tab((*tree)->data);
	path = free_tab(path);
	(*tree)->data = data;
}
