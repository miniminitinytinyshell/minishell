/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 19:18:32 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/03/28 17:04:47 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"
#include "libft.h"

t_token	*token_new(char *data_start, int len, t_token_group group)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		return (NULL);
	new->data = ft_calloc(len + 1, sizeof(char));
	if (!(new->data))
		return (NULL);
	ft_strlcpy(new->data, data_start, len + 1);
	new->group = group;
	new->next = NULL;
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

void	token_clear(t_token **token)
{
	t_token	*tmp;

	while (*token)
	{
		tmp = (*token)->next;
		token_free(*token);
		*token = tmp;
	}
	token = NULL;
}
