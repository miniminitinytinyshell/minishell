/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 18:12:24 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/23 11:48:44 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

void	error_syscall(void)
{
	ft_putstr_fd("mongshell: ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
	if (errno == 13)
		exit (126);
	exit(EXIT_FAILURE);
}

int	error_with_str(char *str, int flag)
{
	ft_putstr_fd("mongshell: ", STDERR_FILENO);
	if (flag == CMD_NFOUND)
		ft_putstr_fd("command not found: ", STDERR_FILENO);
	else if (flag == IS_DIR)
		ft_putstr_fd("is a directory: ", STDERR_FILENO);
	else if (flag == AMB_RDR)
		ft_putstr_fd("ambiguous redirect: ", STDERR_FILENO);
	else
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd(str, STDERR_FILENO);
	if (flag == CMD_NFOUND)
		return (127);
	if (flag == IS_DIR)
		return (126);
	else
		return (1);
}

static char	count_sep(t_token **token, int flag)
{
	t_token	*cur;
	int		l_sep;
	int		r_sep;

	cur = *token;
	l_sep = 0;
	r_sep = 0;
	while (cur)
	{
		if (cur->data[0] == '(')
			l_sep++;
		if (cur->data[0] == ')')
			r_sep++;
		cur = cur->next;
	}
	if (l_sep > r_sep)
		return ('(');
	else if (l_sep < r_sep)
		return (')');
	else
		return (flag);
}

int	error_syntax(char *str, t_token **token, int flag)
{
	ft_putstr_fd("mongshell: ", STDERR_FILENO);
	ft_putstr_fd("syntax error near unexpected token ", STDERR_FILENO);
	ft_putchar_fd('\'', STDERR_FILENO);
	if (flag == '(')
		flag = (int)count_sep(token, flag);
	if (flag)
		ft_putchar_fd((char)flag, STDERR_FILENO);
	else
		ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
	if (token)
		token_clear(token);
	return (0);
}

int	error_not_valid(char *cmd, char *arg)
{
	ft_putstr_fd("mongshell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": not a valid identifier '", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
	return (1);
}
