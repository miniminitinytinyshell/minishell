/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:37:04 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/09 14:28:50 by jaeblee          ###   ########.fr       */
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
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
}

void	set_parent_signal(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	set_heardoc_signal(void)
{
	signal(SIGINT, handle_exit);
	signal(SIGQUIT, SIG_IGN);
}

void	set_builtin_signal(void)
{
	signal(SIGINT, handle_set);
	signal(SIGQUIT, SIG_IGN);
}
