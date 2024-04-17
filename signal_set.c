/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:37:04 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/16 18:17:16 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

void	set_signal(void)
{
	term_print_off();
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	set_child_signal(void)
{
	term_print_on();
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	set_parent_signal(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	set_heredoc_signal(void)
{
	signal(SIGINT, handle_exit);
	signal(SIGQUIT, SIG_IGN);
}

void	set_global_signal(void)
{
	signal(SIGINT, handle_set);
	signal(SIGQUIT, SIG_IGN);
}
