/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:08:24 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/03 18:25:01 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

char	*take_eof(char *str)
{
	int		i;
	char	*eof;

	i = 0;
	eof = (char *)malloc(sizeof(char) * (ft_strlen(str) + 2));
	while (str[i])
	{
		eof[i] = str[i];
		i++;
	}
	eof[i] = '\n';
	eof[i + 1] = '\0';
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
		if (ft_strncmp(read_line, eof, ft_strlen(eof) + 1) == 0)
		{
			free(read_line);
			break ;
		}
		ft_putstr_fd(read_line, fd);
		free(read_line);
	}
	free(eof);
	eof = NULL;
}

void	here_doc(char *end, int *file_in)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		error_pipe();
	pid = fork();
	if (pid == -1)
		error_fork();
	if (pid == 0)
	{
		close(fd[0]);
		process_heredoc(end, fd[1]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
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
