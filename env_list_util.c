/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:46:57 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/04/04 15:41:04 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

void	add_env_back(t_env **head, t_env *new)
{
	t_env	*temp;

	if (!(*head))
	{
		*head = new;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

void	clear_env_list(t_env **head)
{
	t_env	*temp;

	while (*head)
	{
		free((*head)->key);
		free((*head)->value);
		temp = (*head)->next;
		free(*head);
		*head = temp;
	}
}

t_env	*find_env_node(t_env *head, char *key)
{
	while (head)
	{
		if (ft_strncmp(head->key, key, ft_strlen(key) + 1) == 0)
			break;
		head = head->next;
	}
	return (head);
}