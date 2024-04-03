/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:50:50 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/04/03 20:23:14 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"
#include <stdio.h>

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

char	**get_envp_arr(t_env *head)
{
	int		cnt;
	int		idx;
	t_env	*temp;
	char	*env_str;
	char	**env_arr;

	temp = head;
	cnt = 0;
	while (temp)
	{
		cnt++;
		temp = temp->next;
	}
	env_arr = ft_calloc(cnt + 1, sizeof(char *));
	if (!env_arr)
		return (NULL);
	idx = 0;
	temp = head;
	while (idx < cnt)
	{
		env_str = ft_calloc(temp->key_len + temp->val_len + 1, sizeof(char) + 1);
		if (!env_str)
			return (NULL);
		ft_strlcpy(env_str, temp->key, temp->key_len + 1);
		ft_strlcat(env_str, "=", temp->key_len + 2);
		ft_strlcat(env_str, temp->value, temp->key_len + temp->val_len + 2);
		env_arr[idx] = env_str;
		temp = temp->next;
		idx++;
	}
	env_arr[idx] = NULL;
	return (env_arr);
}

t_env	*get_envp_list(char **envp)
{
	t_env	*head;
	t_env	*new;
	char	**temp;

	head = NULL;
	while (*envp)
	{
		temp = ft_split(*envp, '=');
		new = ft_calloc(1, sizeof(t_env));
		if (!temp || !new)
		{
			clear_env_list(&head);
			free(temp);
			free(new);
			return (NULL); // leak 생각 안 한 형태임..
		}
		new->key = temp[0];
		new->key_len = ft_strlen(new->key);
		new->value = temp[1];
		new->val_len = ft_strlen(new->value);
		free(temp);
		add_env_back(&head, new);
		envp++;
	}
	return (head);
}
