/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:50:50 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/04/04 14:00:29 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"
#include <stdio.h>

static int	get_envp_cnt(t_env *head)
{
	int	cnt;

	cnt = 0;
	while (head)
	{
		cnt++;
		head = head->next;
	}
	return (cnt);
}

void	set_envp_data(t_env *head, int cnt, char **env_arr)
{
	int		idx;
	char	*env_str;

	idx = 0;
	while (idx < cnt)
	{
		env_str = ft_calloc(head->key_len + head->val_len + 2, sizeof(char));
		if (!env_str)
		{
			free_tab(env_arr);
			return ;
		}
		ft_strlcpy(env_str, head->key, head->key_len + 1);
		ft_strlcat(env_str, "=", head->key_len + 2);
		ft_strlcat(env_str, head->value, head->key_len + head->val_len + 2);
		env_arr[idx] = env_str;
		head = head->next;
		idx++;
	}
	env_arr[idx] = NULL;
}

char	**get_envp_arr(t_env *head)
{
	const int	cnt = get_envp_cnt(head);
	int			idx;
	char		**env_arr;

	env_arr = ft_calloc(cnt + 1, sizeof(char *));
	if (!env_arr)
		return (NULL);
	idx = 0;
	set_envp_data(head, cnt, env_arr);
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
			free_tab(temp);
			free(new);
			return (NULL);
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
