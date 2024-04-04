/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:22:39 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/04 15:49:56 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

static void	find_path(char *str, char **path)
{
	int		i;
	int		j;

	i = 0;
	j = ft_strlen(str) - 1;
	while (j >= 0)
	{
		if (str[j] == '/')
		{
			path[0] = (char *)malloc(sizeof(char) * (j + 1));
			while (i < j)
			{
				path[0][i] = str[i];
				i++;
			}
			path[0][i] = '\0';
			break ;
		}
		j--;
	}
	j = 0;
	path[1] = (char *)malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	while (str[i])
		path[1][j++] = str[i++];
}

int	expand_wildcard(t_tree **tree, int i)
{
	DIR		*dir;
	char	**path;

	path = (char **)malloc(sizeof(char *) * 2);
	path[0] = NULL;
	path[1] = NULL;
	find_path((*tree)->data[i], path);
	dir = opendir(path);
	if (!dir)
		return ;
	readdir(dir)
}
