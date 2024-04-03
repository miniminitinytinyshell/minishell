/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_open.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:42:08 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/03 17:47:33 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int	main(void)
{
	int	fd;
	int	file_in;

	fd = 0;
	file_in = 0;
	fd = open("test_dir.c", O_RDONLY);
	printf("%d\n", fd);
	fd = close(fd);
	printf("%d\n", fd);
	return (0);
}