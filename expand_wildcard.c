/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:22:39 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/04 14:38:39 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

static char	*find_path(char *str)
{
	int		i;
	int		len;
	char	*path;

	i = 0;
	path = NULL;
	len = ft_strlen(str) - 1;
	while (len >= 0)
	{
		if (str[len] == '/')
		{
			path = (char *)malloc(sizeof(char) * (len + 1));
			while (i < len)
			{
				path[i] = str[i];
				i++;
			}
			path[i] = '\0';
			break;
		}
		len--;
	}
	if (path)
		return (path);
	return (ft_strdup("."));
}

int	expand_wildcard(t_tree **tree, int i)
{
	DIR		*dir;
	char	*path;

	path = find_path((*tree)->data[i]);
	dir = opendir(path);
	if (!dir)
		return ;
	readdir(dir)
}
