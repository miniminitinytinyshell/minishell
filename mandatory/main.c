/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:35:56 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/26 21:29:20 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

volatile sig_atomic_t	g_signum;

static t_envp	set_envp(char **envp)
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
	if (!env.data || !env.pwd)
		error_syscall();
	idx = 0;
	while (envp[idx])
	{
		env.data[idx] = ft_strdup(envp[idx]);
		if (!env.data[idx])
			error_syscall();
		idx++;
	}
	return (env);
}

static int	check_cmd(char *cmd, int *status)
{
	if (g_signum == SIGINT)
	{
		g_signum = 0;
		*status = 1;
	}
	if (!cmd)
	{
		ft_putstr_fd("\033[u\033[1B\033[1A", STDERR_FILENO);
		ft_putendl_fd("exit", STDERR_FILENO);
		exit(*status);
	}
	while (*cmd == ' ')
		cmd++;
	if (!(*cmd))
		return (-1);
	else
		return (0);
}

static int	cnt_heredoc(t_token *token)
{
	int	cnt;

	cnt = 0;
	while (token)
	{
		if (token->group == rdr && ft_strncmp(token->data, "<<", 3) == 0)
			cnt++;
		token = token->next;
	}
	if (cnt > 16)
	{
		ft_putstr_fd("mongshell: ", STDERR_FILENO);
		ft_putendl_fd("maximum here-document count exceeded", STDERR_FILENO);
		exit(2);
	}
	return (cnt);
}

static void	proc_shell(t_envp *envp, int *status, char *cmd)
{
	t_tree	*tree;
	t_token	*token;

	tree = init_tree();
	token = tokenizer(cmd);
	cnt_heredoc(token);
	if (check_pipe(&tree, token) != 0)
		execute_tree(&tree, envp, status);
	else
		*status = 258;
	tree = free_tree(tree);
}

int	main(int argc, char **argv, char **envp)
{
	int		status;
	char	*cmd;
	t_envp	env;

	if (argc > 1)
		return (printf("usage: %s\n", argv[0]));
	status = 0;
	cmd = NULL;
	env = set_envp(envp);
	while (1)
	{
		g_signum = 0;
		set_signal();
		cmd = readline("mongshell\001🐶>\002 \033[s");
		if (check_cmd(cmd, &status) < 0)
			continue ;
		proc_shell(&env, &status, cmd);
		add_history(cmd);
		cmd = free_null(cmd);
	}
	return (0);
}
