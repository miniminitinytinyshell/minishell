/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:33:19 by jaeblee           #+#    #+#             */
/*   Updated: 2024/03/19 23:00:24 by hyeunkim         ###   ########.fr       */
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

int	cnt_token(char *str)
{
	int		cnt;
	int		idx;
	char	sep;

	if (*str == ' ')
		cnt = 0;
	else
		cnt = 1;
	idx = 1;
	sep = 0;
	while (str[idx])
	{
		if (str[idx] == '(' || str[idx] ==')')
		{
			// printf("%c", str[idx]);
			cnt++;
		}
		if (str[idx] == '<' || str[idx] == '>' || str[idx] == '|')
		{
			cnt++;
			// printf("%d:%s\n", idx, str + idx);
			if (str[idx] == str[idx + 1])
				idx++;
			// printf("%d:%s\n", idx, str + idx);
		}
		if (str[idx] == ' ' && str[idx - 1] != ' ')
		{
			// printf("%c", str[idx - 1]);
			cnt++;
		}
		if (str[idx] == '&' && str[idx + 1] == '&')
		{
			// printf("%c", str[idx]);
			cnt++;
			idx++;
		}
		idx++;
		printf("%d: %s\n", cnt, str + idx);
	}
	printf("\n");
	return (cnt);
}
