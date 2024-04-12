/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:46:37 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/12 18:38:55 by jaeblee          ###   ########.fr       */
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
	int		check;
	char	*temp;
	char	*cmd[] = {"ls", NULL};

	temp = getcwd(NULL, 0);
	printf("pwd: %s\n", temp);
	check = chdir("..");
	printf("check = %d\n", check);
	temp = getcwd(NULL, 0);
	printf("pwd: %s\n", temp);
	check = chdir("..");
	printf("check = %d\n", check);
	temp = getcwd(NULL, 0);
	printf("pwd: %s\n", temp);
	return (0);
}
