/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:33:19 by jaeblee           #+#    #+#             */
/*   Updated: 2024/03/22 14:46:19 by hyeunkim         ###   ########.fr       */
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
				while (str[len] && str[len] != quote)
					len++;
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
