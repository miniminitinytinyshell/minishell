/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 19:25:06 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/04/30 20:49:08 by hyeunkim         ###   ########.fr       */
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
