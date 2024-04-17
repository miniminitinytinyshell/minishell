/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:35:56 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/17 19:29:46 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_bonus.h"
#include "function_bonus.h"

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

static void	proc_shell(t_tree **tree, t_envp *envp, int *status, char *cmd)
{
	if (check_pipe(tree, tokenizer(cmd)) != 0)
		execute_tree(tree, envp, status);
	else
		*status = 258;
}

int	test_shell(t_envp envp, int status, char **argv)
{
	int		i;
	char	*cmd;
	t_tree	*tree;

	i = 1;
	cmd = NULL;
	while (argv[i])
	{
		cmd = strjoin_shell(cmd, argv[i]);
		cmd = strjoin_shell(cmd, " ");
		i++;
	}
	tree = init_tree();
	proc_shell(&tree, &envp, &status, cmd);
	tree = free_tree(tree);
	exit(status);
}

int	main(int argc, char **argv, char **envp)
{
	int		status;
	char	*cmd;
	t_envp	env;
	t_tree	*tree;

	status = 0;
	cmd = NULL;
	env = set_envp(envp);
	if (argc > 1)
		test_shell(env, status, argv);
	while (1)
	{
		g_signum = 0;
		set_signal();
		cmd = readline("mongshell🐶 ");
		if (check_cmd(cmd) < 0)
			continue ;
		tree = init_tree();
		proc_shell(&tree, &env, &status, cmd);
		add_history(cmd);
		cmd = free_null(cmd);
		tree = free_tree(tree);
	}
	return (0);
}
