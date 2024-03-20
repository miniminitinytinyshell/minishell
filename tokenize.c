/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:33:19 by jaeblee           #+#    #+#             */
/*   Updated: 2024/03/20 13:32:36 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*ft_strchr(const char *str, int val)
{
	size_t	len;

	val %= 256;
	len = ft_strlen(str);
	if (!val)
		return ((char *)str + len);
	while (*str)
	{
		if (*str == val)
			return ((char *)str);
		str++;
	}
	return (NULL);
}

int	count_token(char *str)
{
	int		cnt;
	int		idx;
	char	sep;
	char	*meta = "<>()|& ";

	if (*str == ' ')
		cnt = 0;
	else
		cnt = 1;
	idx = 1;
	while (str[idx])
	{
		sep = 0;
		if (sep == 0 && (str[idx] == '\'' || str[idx] == '"'))
		{
			sep = str[idx];
			idx++;
			while (sep != 0 && str[idx] != sep)
				idx++;
			sep = 0;
		}
		// if (str[idx] == ' ' && str[idx - 1] != ' ' && !ft_strchr(meta, str[idx - 1]))
		// {
		// 	printf("%3d,%3d:%s\n", idx, cnt, str + idx);
		// 	cnt++;
		// }
		if (!ft_strchr(meta, str[idx]) && ft_strchr(meta, str[idx - 1]))
		{
			printf("%3d,%3d:%s\n", idx ,cnt, str + idx);
			cnt++;
		}
		if (ft_strchr(meta, str[idx]) != ft_strchr(meta, str[idx - 1]))
		{
			printf("%3d,%3d:%s\n", idx ,cnt, str + idx);
			cnt++;
		}
		idx++;
	}
	return (cnt);
}
