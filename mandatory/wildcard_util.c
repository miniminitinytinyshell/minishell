/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:45:43 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/20 05:02:33 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

static char	*strdup_sf(char *str, int s, int f)
{
	int		i;
	int		size;
	char	*result;

	i = 0;
	size = f - s + 2;
	if (f == -1)
		result = ft_strdup(".");
	else if (s > f)
		result = NULL;
	else
	{
		result = ft_calloc(size, sizeof(char));
		while (s <= f)
		{
			result[i] = str[s];
			i++;
			s++;
		}
	}
	return (result);
}

static int	find_front_path(char *str, int star)
{
	int	idx;

	idx = star;
	while (idx >= 0)
	{
		if (str[idx] == '/')
			break ;
		idx -= 1;
	}
	return (idx);
}

static int	find_back_path(char *str, int star)
{
	int	idx;

	idx = star;
	while (str[idx])
	{
		if (str[idx] == '/')
			break ;
		idx++;
	}
	return (idx);
}

int	extract_path(char *str, char **path)
{
	int	star;
	int	f_path;
	int	b_path;

	star = 0;
	while (str[star] != '*')
		star++;
	f_path = find_front_path(str, star);
	b_path = find_back_path(str, star);
	if (b_path == -1)
		return (1);
	path[0] = strdup_sf(str, 0, f_path);
	path[1] = strdup_sf(str, f_path + 1, b_path - 1);
	path[2] = strdup_sf(str, b_path, strlen(str) - 1);
	return (0);
}
