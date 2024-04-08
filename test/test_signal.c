/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:48:58 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/08 17:48:28 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <termios.h>
#include <readline/history.h>
#include <readline/readline.h>

void	term_print_off(void)
{
	struct termios	term_attr;

	tcgetattr(STDIN_FILENO, &term_attr);
	term_attr.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term_attr);
}

void test_signal_handler(int signum)
{
	write(2, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void child_signal_handler(int signum)
{
	printf("Child received signal %d\n", signum);
	rl_replace_line("", 0);
	exit(EXIT_SUCCESS);
}

int main()
{
	pid_t	pid;
	char	*line;
	char	*cmd[] = {"/bin/cat", NULL};

	line = NULL;
	term_print_off();
	while (1)
	{
		if (line)
		{
			free(line);
			line = NULL;
		}
		line = readline("TEST> ");
		if (!line)
			exit(EXIT_SUCCESS);
		pid = fork();
		if (pid < 0)
			exit(EXIT_FAILURE);
		if (pid == 0)
		{
			// signal(SIGINT, child_signal_handler);
			execve(*cmd, cmd, NULL);
			exit(EXIT_SUCCESS);
		}
		else
		{
			signal(SIGINT, test_signal_handler);
			waitpid(pid, NULL, 0);
		}
	}
	return 0;
}