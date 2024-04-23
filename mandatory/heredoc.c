/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:08:24 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/23 13:37:36 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

extern volatile sig_atomic_t	g_signum;

int	heredoc_env(char *str, int fd, t_envp *envp)
{
	int		env_len;
	char	*key;
	char	*value;

	str++;
	env_len = 0;
	while (str[env_len] && (ft_isalnum(str[env_len]) || str[env_len] == '_'))
		env_len++;
	key = ft_calloc(env_len + 1, sizeof(char));
	if (!key)
		error_syscall();
	ft_strlcpy(key, str, env_len + 1);
	value = find_env(key, envp->data);
	if (!value)
		value = ft_strdup("");
	if (!value)
		error_syscall();
	ft_putstr_fd(value, fd);
	free(key);
	free(value);
	return (env_len);
}

void	read_heredoc(char *eof, int fd, t_envp *envp, int flag)
{
	int		idx;
	char	*read_line;

	while (1)
	{
		read_line = readline("heredoc> ");
		if (!read_line || ft_strncmp(read_line, eof, ft_strlen(eof) + 1) == 0)
		{
			read_line = free_null(read_line);
			break ;
		}
		idx = 0;
		while (read_line[idx])
		{
			if (flag == 0 && read_line[idx] == '$')
				idx += heredoc_env(read_line + idx, fd, envp);
			else
				ft_putchar_fd(read_line[idx], fd);
			idx++;
		}
		ft_putendl_fd("", fd);
		read_line = free_null(read_line);
	}
	exit(EXIT_SUCCESS);
}

void	fork_heredoc(char *eof, int fd, t_envp *envp)
{
	int		flag;
	pid_t	pid;
	char	*exp_eof;

	pid = fork();
	if (pid == -1)
		error_syscall();
	if (pid == 0)
	{
		flag = 0;
		set_heredoc_signal();
		if (ft_strchr(eof, '\'') || ft_strchr(eof, '"'))
			flag = 1;
		exp_eof = expand_word(eof, NULL, 0);
		if (!exp_eof)
			read_heredoc(eof, fd, envp, flag);
		else
			read_heredoc(exp_eof, fd, envp, flag);
		free(exp_eof);
	}
	else
	{
		set_global_signal();
		waitpid(pid, NULL, 0);
	}
}

void	create_heredoc(t_tree **tree, int *name, t_envp *envp)
{
	int		fd;
	char	*path;

	path = NULL;
	if ((*tree)->type == rdr_cmd)
	{
		if (ft_strncmp((*tree)->data[0], "<<", 3) == 0)
		{
			path = strjoin_free(ft_strdup("/tmp/temp_"), ft_itoa(*name));
			fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			fork_heredoc((*tree)->data[1], fd, envp);
			close(fd);
			free((*tree)->data[1]);
			(*tree)->data[1] = path;
			*name += 1;
		}
	}
	else
	{
		if ((*tree)->left && g_signum != SIGINT)
			create_heredoc(&(*tree)->left, name, envp);
		if ((*tree)->right && g_signum != SIGINT)
			create_heredoc(&(*tree)->right, name, envp);
	}
}

void	delete_heredoc(t_tree **tree)
{
	if (!tree && !(*tree))
		return ;
	if ((*tree)->type == rdr_cmd)
	{
		if (access((*tree)->data[1], F_OK) == 0)
			unlink((*tree)->data[1]);
	}
	else
	{
		if ((*tree)->left)
			delete_heredoc(&(*tree)->left);
		if ((*tree)->right)
			delete_heredoc(&(*tree)->right);
	}
}
