/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:33:19 by jaeblee           #+#    #+#             */
/*   Updated: 2024/03/22 14:12:37 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"
#include "libft.h"

t_token_type set_token_type(char *data, int len)
{
	if (!ft_strncmp(data, "(", len))
		return (left_par);
	else if (!ft_strncmp(data, ")", len))
		return (right_par);
	else if (!ft_strncmp(data, "||", len))
		return (logic_or);
	else if (!ft_strncmp(data, "&&", len))
		return (logic_and);
	else if (!ft_strncmp(data, "|", len))
		return (pipe_op);
	else if (!ft_strncmp(data, "<<", len))
		return (here_doc);
	else if (!ft_strncmp(data, "<", len))
		return (in_trunc);
	else if (!ft_strncmp(data, ">>", len))
		return (out_append);
	else if (!ft_strncmp(data, ">", len))
		return (out_trunc);
	else
		return (word);
}

int	token_len(char *str)
{
	int		len;
	char	quote_type;

	len = 0;
	if (str[0] == '(' || str[0] == ')')
		len = 1;
	else if (ft_strchr("<>|&", str[0]))
		while (str[len] == str[0])
			len++;
	else
	{
		while (str[len] && !ft_strchr("()<>|& ", str[len]))
		{
			if (str[len] == '\'' || str[len] == '"')
			{
				quote_type = str[len];
				len++;
				while (str[len] && str[len] != quote_type)
					len++;
			}
			len++;
		}
	}
	return (len);
}

void	tokenizer(t_token **token, char *str)
{
	int		len;
	t_token	*new;

	while (*str)
	{
		while (*str == ' ')
			str++;
		len = token_len(str);
		new = token_new(str, len, set_token_type(str, len));
		str += len;
		token_add_back(token, new);
	}
}
