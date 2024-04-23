/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:33:19 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/23 14:51:21 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

int	token_len_meta(char *str)
{
	int	len;

	len = 0;
	if (str[0] == '(' || str[0] == ')')
		len = 1;
	else if (ft_strchr("<>|&", str[0]))
	{
		if (str[0] == str[1])
			len = 2;
		else
			len = 1;
	}
	if (str[0] == '&' && str[1] != str[0])
		len = -1;
	return (len);
}

int	token_len_word(char *str)
{
	char	quote;
	int		len;

	len = 0;
	while (str[len] && !ft_strchr("()<>|& ", str[len]))
	{
		if (str[len] > 8 && str[len] < 14)
			break ;
		if (str[len] == '\'' || str[len] == '"')
		{
			quote = str[len];
			len++;
			while (str[len] != quote)
			{
				if (str[len] == '\0')
					return ((int)((-1) * quote));
				len++;
			}
		}
		len++;
	}
	return (len);
}

int	token_len(char *str)
{
	int	len;

	if (*str == '\0')
		return (0);
	if (ft_strchr("()<>|&", str[0]))
		len = token_len_meta(str);
	else
		len = token_len_word(str);
	return (len);
}

void	token_extend(char *str, int len, t_token **token)
{
	t_token	*new;

	new = token_new(str, len);
	if (!new)
	{
		token_clear(token);
		error_syscall();
	}
	token_add_back(token, new);
}

t_token	*tokenizer(char *str)
{
	int		len;
	t_token	*token;

	token = NULL;
	if (!str)
		return (token);
	while (*str)
	{
		while (*str == ' ' || (8 < *str && *str < 14))
			str++;
		len = token_len(str);
		if (len < 0)
		{
			error_syntax(str, &token, len * (-1));
			return (NULL);
		}
		else if (len == 0)
			continue ;
		token_extend(str, len, &token);
		str += len;
	}
	return (token);
}
