/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:33:19 by jaeblee           #+#    #+#             */
/*   Updated: 2024/03/20 19:19:21 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"
#include "libft.h"

int	token_len(char *str)
{
	int		len;
	char	quote_type;

	len = 0;
	while (str[len])
	{
		if (ft_strchr("()<>|&", str[0]))
		{
			while (str[len] == str[0])
				len++;
			break ;
		}
		if (str[len] == '\'' || str[len] == '"')
		{
			quote_type = str[len];
			len++;
			while (str[len] != quote_type)
				len++;
		}
		if (ft_strchr("()<>|& ", str[len]))
			break ;
		len++;
	}
	return (len);
}

void	tokenizer(t_token **token, char *str)
{
	int		len;
	t_token	*new;

	while (*str)
	{
		if (*str == ' ')
			while (*str == ' ')
				str++;
		else
		{
			len = token_len(str);
			if (*str == '(' || *str == ')')
				new = token_new(str, len, sep);
			else if (*str == '|' || *str == '&')
				new = token_new(str, len, con_op);
			else if (*str == '<' || *str == '>')
				new = token_new(str, len, re_op);
			else
				new = token_new(str, len, word);
			str += len;
			token_add_back(token, new);
		}
	}
}
