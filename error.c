/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 18:12:24 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/03 18:04:27 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

int	error_malloc(t_token **token)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (token)
		token_clear(token);
	ft_putendl_fd("malloc error", STDERR_FILENO);
	return (0);
}

int	error_syntax(char *str, t_token **token, int flag)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("syntax error near unexpected token ", STDERR_FILENO);
	ft_putchar_fd('\'', STDERR_FILENO);
	if (flag)
		ft_putchar_fd((char)flag, STDERR_FILENO);
	else
		ft_putchar_fd(*str, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
	if (token)
		token_clear(token);
	return (0);
}

int	error_cmd_not_found(char *cmd)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("command not found: ", STDERR_FILENO);
	ft_putendl_fd(cmd, STDERR_FILENO);
	exit(127);
}

int	error_no_file(char *cmd)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("no such file or directory: ", STDERR_FILENO);
	ft_putendl_fd(cmd, STDERR_FILENO);
	exit(127);
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

void	error_cd(void)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
	exit(EXIT_FAILURE);
}
