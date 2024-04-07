/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_system.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:20:08 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/07 11:04:27 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

void	error_fork(void)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putendl_fd("fork error", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	error_pipe(void)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putendl_fd("pipe error", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	error_syscall(void)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
	exit(EXIT_FAILURE);
}