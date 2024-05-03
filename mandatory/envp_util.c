/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 19:25:06 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/05/03 21:23:31 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

t_envp	init_envp(char **envp)
{
	t_envp	env;
	int		idx;

	idx = 0;
	while (envp[idx])
		idx++;
	env.max_cnt = idx;
	env.curr_cnt = idx;
	env.path = NULL;
	env.data = ft_calloc(idx + 1, sizeof(char *));
	if (!env.data)
		error_syscall();
	idx = 0;
	while (envp[idx])
	{
		if (ft_strncmp(envp[idx], "OLDPWD", ft_strlen("OLDPWD")) == 0)
			env.data[idx] = ft_strdup("OLDPWD");
		else
			env.data[idx] = ft_strdup(envp[idx]);
		if (!env.data[idx])
			error_syscall();
		idx++;
	}
	adjust_envp(&env);
	return (env);
}

void	adjust_envp(t_envp *envp)
{
	char	*tmp;
	char	**pwd_arr;

	if (get_envp_idx("PATH", envp) < 0)
	{
		envp->path = ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
		if (!envp->path)
			error_syscall();
	}
	envp->pwd = find_env("PWD", envp->data);
	if (!envp->pwd)
		envp->pwd = getcwd(NULL, 0);
	if (!envp->pwd)
		error_syscall();
	tmp = ft_strjoin("PWD=", envp->pwd);
	pwd_arr = ft_calloc(3, sizeof(char *));
	if (!pwd_arr)
		error_syscall();
	pwd_arr[0] = ft_strdup("export");
	if (!pwd_arr[0])
		error_syscall();
	pwd_arr[1] = tmp;
	builtin_export(pwd_arr, envp);
	free_tab(pwd_arr);
}

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
		if (ft_strncmp(envp->data[idx], key, ft_strlen(key)) == 0 \
			&& envp->data[idx][ft_strlen(key)] == '=')
			break ;
		idx++;
	}
	if (idx == envp->curr_cnt)
		return (-1);
	return (idx);
}
