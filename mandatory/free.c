/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:03:26 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/15 14:25:22 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

void	*free_null(void *temp)
{
	if (!temp)
		return (NULL);
	free(temp);
	temp = NULL;
	return (temp);
}

char	**free_tab(char **temp)
{
	int	i;

	i = 0;
	while (temp[i])
	{
		free(temp[i]);
		temp[i] = NULL;
		i++;
	}
	free(temp);
	temp = NULL;
	return (temp);
}
