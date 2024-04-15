/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:08:24 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/15 14:32:34 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

extern int	g_signum;

void	read_heredoc(char *eof, int fd)
{
	char	*read_line;

	while (1)
	{
		read_line = readline("heredoc> ");
		if (!read_line)
			break ;
		if (ft_strncmp(read_line, eof, ft_strlen(eof) + 1) == 0)
		{
			free(read_line);
			read_line = NULL;
			break ;
		}
		ft_putendl_fd(read_line, fd);
		read_line = free_null(read_line);
	}
	exit(EXIT_SUCCESS);
}

void	fork_heredoc(char *eof, int fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error_syscall();
	if (pid == 0)
	{
		set_heardoc_signal();
		read_heredoc(eof, fd);
	}
	else
	{
		set_global_signal();
		waitpid(pid, NULL, 0);
	}
}

void	create_heardoc(t_tree **tree, int *name)
{
	int		fd;
	char	*path;

	path = NULL;
	if ((*tree)->type == rdr_cmd)
	{
		if (ft_strncmp((*tree)->data[0], "<<", 3) == 0)
		{
			path = strjoin_free(ft_strdup("./.temp_"), ft_itoa(*name));
			fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			fork_heredoc((*tree)->data[1], fd);
			close(fd);
			free((*tree)->data[1]);
			(*tree)->data[1] = path;
			*name += 1;
		}
	}
	else
	{
		if ((*tree)->left && g_signum != SIGINT)
			create_heardoc(&(*tree)->left, name);
		if ((*tree)->right && g_signum != SIGINT)
			create_heardoc(&(*tree)->right, name);
	}
}

void	delete_heardoc(t_tree **tree)
{
	if (!tree && !(*tree))
		return ;
	if ((*tree)->type == rdr_cmd)
	{
		unlink((*tree)->data[1]);
	}
	else
	{
		if ((*tree)->left)
			delete_heardoc(&(*tree)->left);
		if ((*tree)->right)
			delete_heardoc(&(*tree)->right);
	}
}
