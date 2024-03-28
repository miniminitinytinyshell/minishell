/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:32:36 by jaeblee           #+#    #+#             */
/*   Updated: 2024/03/28 17:42:51 by jaeblee          ###   ########.fr       */
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
