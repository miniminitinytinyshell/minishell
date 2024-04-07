/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:22:39 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/07 15:08:11 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

static void	find_path(char *str, char **path)
{
	int	i;
	int	j;

	i = ft_strlen(str);
	while (i > 0)
	{
		if (str[i - 1] == '/')
			break ;
		i--;
	}
	path[0] = (char *)malloc(sizeof(char) * (i + 1));
	path[1] = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1 - i));
	if (i == 0)
		path[0] = ft_strdup(".");
	else
	{
		j = -1;
		while (++j < i)
			path[0][j] = str[j];
		path[0][j] = '\0';
	}
	j = 0;
	while (str[i])
		path[1][j++] = str[i++];
	path[1][j] = '\0';
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

char	**table_join(char **tab, char *data)
{
	int		i;
	char	**result;

	if (!tab)
	{
		result = (char **)malloc(sizeof(char *) * 2);
		result[0] = data;
		result[1] = NULL;
		return (result);
	}
	i = 0;
	while (tab[i])
		i++;
	result = (char **)malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (tab[i])
	{
		result[i] = ft_strdup(tab[i]);
		i++;
	}
	result[i] = data;
	result[i + 1] = NULL;
	free_tab(tab);
	return (result);
}

char	**table_dup(char **tab, int size)
{
	int		i;
	char	**result;

	i = 0;
	result = NULL;
	while (i < size)
	{
		result = table_join(result, ft_strdup(tab[i]));
		i++;
	}
	return (result);
}

int	expand_wildcard(t_tree **tree, int i)
{
	DIR				*dir;
	char			**path;
	char			**data;
	struct dirent	*file;

	path = (char **)malloc(sizeof(char *) * 2);
	find_path((*tree)->data[i], path);
	dir = opendir(path[0]);
	if (!dir)
		return (0);
	data = table_dup((*tree)->data, i);
	while (1)
	{
		file = readdir(dir);
		if (!file)
			break ;
		if (file->d_name[0] != '.' && match(path[1], file->d_name))
			data = table_join(data, ft_strjoin(path[0], file->d_name));
	}
	closedir(dir);
	while ((*tree)->data[++i])
		data = table_join(data, ft_strdup((*tree)->data[i]));
	free_tab((*tree)->data);
	(*tree)->data = data;
	return (1);
}
