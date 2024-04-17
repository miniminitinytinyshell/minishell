/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:22:39 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/17 15:02:46 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_bonus.h"
#include "function_bonus.h"

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

static int	add_wildcard_data(char ***data, char **path, DIR *dir)
{
	int				cnt;
	struct dirent	*file;

	cnt = 0;
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
			cnt++;
		}
	}
	if (cnt == 0)
	{
		*data = table_join(*data, ft_strdup(path[1]));
		cnt++;
	}
	return (cnt);
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

void	expand_wildcard(t_tree **tree, int *i)
{
	int				cnt;
	DIR				*dir;
	char			**path;
	char			**data;

	path = ft_calloc(3, sizeof(char *));
	if (!path)
		error_syscall();
	extract_path((*tree)->data[*i], path);
	dir = opendir(path[0]);
	if (!dir)
	{
		free_tab(path);
		return ;
	}
	data = table_dup((*tree)->data, *i);
	cnt = add_wildcard_data(&data, path, dir);
	closedir(dir);
	data = add_remain_data(tree, data, *i);
	*i += cnt - 1;
	free_tab((*tree)->data);
	path = free_tab(path);
	(*tree)->data = data;
}
