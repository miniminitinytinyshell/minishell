/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:32:36 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/17 19:30:41 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_bonus.h"
#include "function_bonus.h"

char	*strjoin_char(char *str, char c)
{
	int		i;
	char	*word;

	i = 0;
	if (str)
	{
		word = ft_calloc(ft_strlen(str) + 2, sizeof(char));
		if (!str)
			error_syscall();
		while (str[i])
		{
			word[i] = str[i];
			i++;
		}
		free(str);
	}
	else
	{
		word = ft_calloc(2, sizeof(char));
		if (!word)
			error_syscall();
	}
	word[i] = c;
	return (word);
}

char	*strjoin_shell(char *str1, char *str2)
{
	char	*result;

	result = NULL;
	if (!str1)
		result = ft_strdup(str2);
	else
		result = ft_strjoin(str1, str2);
	if (str1)
		free(str1);
	return (result);
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

	if (!data)
		return (tab);
	if (!tab)
	{
		result = ft_calloc(2, sizeof(char *));
		result[0] = data;
		return (result);
	}
	i = 0;
	while (tab[i])
		i++;
	result = ft_calloc(i + 2, sizeof(char *));
	i = 0;
	while (tab[i])
	{
		result[i] = ft_strdup(tab[i]);
		i++;
	}
	result[i] = data;
	free_tab(tab);
	return (result);
}
