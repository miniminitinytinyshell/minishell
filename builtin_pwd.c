/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 18:45:00 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/04/06 18:48:33 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

int	pwd_error(void)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("pwd: ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
	return (EXIT_FAILURE);
}

int	builtin_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (pwd_error());
	ft_putendl_fd(pwd, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}