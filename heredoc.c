/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:08:24 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/09 16:35:03 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

char	*take_eof(char *str)
{
	int		i;
	char	*eof;

	eof = ft_calloc(ft_strlen(str) + 2, sizeof(char));
	i = 0;
	while (str[i])
	{
		eof[i] = str[i];
		i++;
	}
	eof[i] = '\n';
	return (eof);
}

void	process_heredoc(char *end, int fd)
{
	char	*eof;
	char	*read_line;

	eof = take_eof(end);
	while (1)
	{
		ft_putstr_fd("heredoc> ", 1);
		read_line = get_next_line(STDIN_FILENO);
		if (!read_line)
		{
			ft_putstr_fd("\n", STDERR_FILENO);
			break ;
		}
		if (ft_strncmp(read_line, eof, ft_strlen(eof) + 1) == 0)
		{
			free(read_line);
			read_line = NULL;
			break ;
		}
		ft_putstr_fd(read_line, fd);
		read_line = free_null(read_line);
	}
	eof = free_null(eof);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	here_doc(char *end, int *file_in)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		error_syscall();
	pid = fork();
	if (pid == -1)
		error_syscall();
	if (pid == 0)
	{
		set_heardoc_signal();
		close(fd[0]);
		process_heredoc(end, fd[1]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(fd[1]);
		waitpid(pid, NULL, 0);
		*file_in = 100;
		dup2(fd[0], *file_in);
		close(fd[0]);
	}
}
