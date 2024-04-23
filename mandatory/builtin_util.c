/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:36:03 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/04/22 14:41:43 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

int	swap_envp_data(char *key, char *value, t_envp *envp)
{
	int		idx;
	char	*new_env;
	char	*temp;

	idx = get_envp_idx(key, envp);
	if (idx < 0)
		return (1);
	if (!value)
		return (0);
	if (value[0] == '=')
		value += 1;
	new_env = ft_calloc(ft_strlen(key) + ft_strlen(value) + 2, sizeof(char));
	if (!new_env)
		error_syscall();
	ft_strlcpy(new_env, key, ft_strlen(key) + 1);
	new_env[ft_strlen(key)] = '=';
	ft_strlcat(new_env, value, ft_strlen(key) + ft_strlen(value) + 2);
	temp = envp->data[idx];
	envp->data[idx] = new_env;
	free(temp);
	return (0);
}

int	get_envp_idx(char *key, t_envp *envp)
{
	int	idx;

	idx = 0;
	while (idx < envp->curr_cnt)
	{
		if (ft_strncmp(envp->data[idx], key, ft_strlen(key)) == 0)
			break ;
		idx++;
	}
	if (idx == envp->curr_cnt)
		return (-1);
	return (idx);
}
