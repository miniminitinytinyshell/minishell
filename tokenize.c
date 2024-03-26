/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:33:19 by jaeblee           #+#    #+#             */
/*   Updated: 2024/03/26 17:37:51 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"
#include "libft.h"

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
		if (str[len] == '\'' || str[len] == '"')
		{
			quote = str[len];
			len++;
			while (str[len] != quote)
			{
				if (str[len] == '\0')
					return (-1);
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

	if (ft_strchr("()<>|&", str[0]))
		len = token_len_meta(str);
	else
		len = token_len_word(str);
	return (len);
}

void	tokenizer(t_token **token, char *str)
{
	int				len;
	t_token			*new;

	while (*str)
	{
		while (*str == ' ')
			str++;
		len = token_len(str);
		// printf("%d\n", len);
		if (len < 0)
		{
			token_clear(token);
			*token = NULL;
			return ;
		}
		if (*str == '(' || *str == ')')
			new = token_new(str, len, sep);
		else if (*str == '<' || *str == '>')
			new = token_new(str, len, rdr);
		else if (*str == '|' || *str == '&')
			new = token_new(str, len, con);
		else
			new = token_new(str, len, word);
		str += len;
		token_add_back(token, new);
	}
}
