/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:35:56 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/16 20:41:16 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

int	g_signum;

t_envp	set_envp(char **envp)
{
	t_envp	env;
	int		idx;

	idx = 0;
	while (envp[idx])
		idx++;
	env.max_cnt = idx;
	env.curr_cnt = idx;
	env.data = ft_calloc(idx + 1, sizeof(char *));
	env.pwd = getcwd(NULL, 0);
	if (!env.pwd)
		error_syscall();
	idx = 0;
	while (envp[idx])
	{
		(env.data)[idx] = ft_strdup(envp[idx]);
		idx++;
	}
	return (env);
}

int	check_cmd(char *cmd)
{
	if (!cmd)
		exit(EXIT_SUCCESS);
	while (*cmd == ' ')
		cmd++;
	if (!(*cmd))
		return (-1);
	else
		return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int		status;
	char	*cmd;
	t_envp	env;
	t_tree	*tree;

	if (argc > 1)
		return (printf("usage: %s\n", argv[0]));
	status = 0;
	cmd = NULL;
	env = set_envp(envp);
	while (1)
	{
		g_signum = 0;
		set_signal();
		cmd = readline("minishell$ ");
		if (check_cmd(cmd) < 0)
			continue ;
		tree = init_tree();
		if (check_pipe(&tree, tokenizer(cmd)) != 0)
			execute_tree(&tree, &env, &status);
		add_history(cmd);
		cmd = free_null(cmd);
		tree = free_tree(tree);
	}
	return (0);
}
