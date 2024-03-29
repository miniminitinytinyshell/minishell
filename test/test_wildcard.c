/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_wildcard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:13:39 by jaeblee           #+#    #+#             */
/*   Updated: 2024/03/29 13:22:10 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int	main(int ac, char **av)
{
	// char	**cmd = {"/bin/ls", "*.c", NULL};
	// execve(*cmd, cmd, NULL);
	int		size;
	char	test[1024];

	size = read(1, test, 1024);
	while (size > 0)
	{
		test[size] = '\0';
		printf("%s", test);
		size = read(1, test, 1024);
	}
	return (0);
}