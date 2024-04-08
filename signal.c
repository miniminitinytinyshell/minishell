/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 14:18:01 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/08 16:11:38 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

void	term_print_off(void)
{
	struct termios	term_attr;

	tcgetattr(STDIN_FILENO, &term_attr);
	term_attr.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term_attr);
}

void	handle_fork(int signum)
{
	if (signum != SIGINT)
		return ;
	exit(EXIT_FAILURE);
}

void	handle_sigint(int signum)
{
	if (signum != SIGINT)
		return ;
	ft_putstr_fd("\n", STDERR_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	set_fork_signal(void)
{
	// printf("HERE\n", STDOUT_FILENO);
	signal(SIGINT, handle_fork);
	signal(SIGQUIT, SIG_IGN);
}
