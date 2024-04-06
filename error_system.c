/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_system.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:20:08 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/06 14:21:41 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

int	error_malloc(void)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putendl_fd("malloc error", STDERR_FILENO);
	return (0);
}

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
