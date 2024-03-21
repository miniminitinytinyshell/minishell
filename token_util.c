/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 19:18:32 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/03/20 19:20:25 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"
#include "libft.h"

t_token	*token_new(char *data_start, int len, t_token_type type)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		exit(EXIT_FAILURE);
	new->data = ft_calloc(len + 1, sizeof(char));
	if (!new)
		exit(EXIT_FAILURE);
	ft_strlcpy(new->data, data_start, len + 1);
	new->type = type;
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

void	token_clear(t_token **token)
{
	t_token	*tmp;

	while (*token)
	{
		tmp = (*token)->next;
		free((*token)->data);
		free(*token);
		*token = tmp;
	}
	token = NULL;
}