/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:20:10 by jaeblee           #+#    #+#             */
/*   Updated: 2024/03/19 17:24:22 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int	main(int ac, char **av, char **envp)
{
	char *argv[3] = {"ls", "-l", (char*)NULL};

	execve("/bin/ls", argv, NULL);
	return (0);
}
