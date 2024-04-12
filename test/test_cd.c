/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:46:37 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/12 17:55:35 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

int main(void)
{
	char	*temp;
	char	*cmd[] = {"ls", NULL};

	temp = getcwd(NULL, 0);
	printf("pwd: %s\n", temp);
	chdir("/Users/jaeblee");
	temp = getcwd(NULL, 0);
	printf("pwd: %s\n", temp);
	chdir("goinfre");
	temp = getcwd(NULL, 0);
	printf("pwd: %s\n", temp);
	execve("/bin/ls", cmd, NULL);
	return (0);
}
