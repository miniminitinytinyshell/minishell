/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:08:24 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/09 17:29:02 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

void	process_heredoc(char *eof, int fd)
{
	char	*read_line;

	while (1)
	{
		read_line = readline("heardoc> ");
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
