/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 19:18:32 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/04/23 13:49:36 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

t_token	*token_new(char *str, int len)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		return (NULL);
	new->data = ft_calloc(len + 1, sizeof(char));
	if (!(new->data))
		return (NULL);
	ft_strlcpy(new->data, str, len + 1);
	if (*str == '(' || *str == ')')
		new->group = sep;
	else if (*str == '<' || *str == '>')
		new->group = rdr;
	else if (*str == '|' || *str == '&')
		new->group = con;
	else
		new->group = word;
	return (new);
}

void	token_add_back(t_token **token, t_token *new)
{
	t_token	*curr;

	if (!(*token))
	{
		*token = new;
		return ;
	}
	curr = *token;
	while (curr->next)
		curr = curr->next;
	curr->next = new;
}

int	get_token_size(t_token *token)
{
	int		size;
	t_token	*cur;

	size = 0;
	cur = token;
	while (cur)
	{
		cur = cur->next;
		size++;
	}
	return (size);
}

t_token	*token_free(t_token *token)
{
	if (!token)
		return (token);
	free((token)->data);
	free(token);
	token = NULL;
	return (token);
}

int	token_clear(t_token **token)
{
	t_token	*tmp;

	while (*token)
	{
		tmp = (*token)->next;
		*token = token_free(*token);
		*token = tmp;
	}
	token = NULL;
	return (0);
}
