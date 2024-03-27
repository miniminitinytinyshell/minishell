/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:48:57 by jaeblee           #+#    #+#             */
/*   Updated: 2024/03/27 18:48:58 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char	**dup_envp(char **envp)
{
	int		i;
	char	**temp;

	i = 0;
	while (envp[i])
		i++;
	temp = (char **)malloc(sizeof(char *) * (i + 1));
	if (!temp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		temp[i] = strdup(envp[i]);
		i++;
	}
	return (temp);
}

int	main(int ac, char **av, char **envp)
{
	int		i;
	char	**env;
	char	*cmd[] = {"/usr/bin/touch", "test", NULL};

	i = 0;
	env = dup_envp(envp);
	while (env[i])
	{
		if (strncmp("PWD=", env[i], 4) == 0)
		{
			env[i] = strdup("PWD=/Users/jaeblee/Team_Prj");
			break ;
		}
		i++;
	}
	execve(*cmd, cmd, env);
	return (0);
}
