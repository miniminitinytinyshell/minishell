/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:32:36 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/07 18:46:05 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

char	*strjoin_char(char *str, char c)
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

char	*strjoin_free(char *str1, char *str2)
{
	char	*result;

	result = NULL;
	if (str1 && str2)
		result = ft_strjoin(str1, str2);
	else if (str1 && !str2)
		result = ft_strdup(str1);
	else if (!str1 && str2)
		result = ft_strdup(str2);
	if (str1)
		free(str1);
	if (str2)
		free(str2);
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
