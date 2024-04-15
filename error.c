/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 18:12:24 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/15 19:37:08 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

void	error_syscall(void)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
	exit(EXIT_FAILURE);
}

int	error_no_file(char *cmd)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("No such file or directory: ", STDERR_FILENO);
	ft_putendl_fd(cmd, STDERR_FILENO);
	return (1);
}

int	error_permission(char *file)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("Permisiion denied: ", STDERR_FILENO);
	ft_putendl_fd(file, STDERR_FILENO);
	return (1);
}

int	error_is_directory(char *path)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("is a directory: ", STDERR_FILENO);
	ft_putendl_fd(path, STDERR_FILENO);
	return (1);
}

int	error_cmd_not_found(char *cmd)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("command not found: ", STDERR_FILENO);
	ft_putendl_fd(cmd, STDERR_FILENO);
	exit (127);
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
