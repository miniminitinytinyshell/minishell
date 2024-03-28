/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 18:12:24 by jaeblee           #+#    #+#             */
/*   Updated: 2024/03/28 19:09:12 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

int	error_malloc(t_token **token)
{
	if (token)
		token_clear(token);
	ft_putendl_fd("malloc error", 2);
	return (0);
}

int	error_syntax(char *str, t_token **token)
{
	ft_putstr_fd("syntax error near unexpected token", 2);
	printf(" '%s'\n", str);
	if (token)
		token_clear(token);
	return (0);
}
