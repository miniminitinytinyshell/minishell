/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:48:52 by jaeblee           #+#    #+#             */
/*   Updated: 2024/03/27 18:48:53 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void execute_touch(const char *path) {
	if (path == NULL)
	{
		printf("Usage: ./a.out <file_path>\n");
		exit(EXIT_FAILURE);
	}

	if (access(path, F_OK) == -1)
	{
		FILE *fp = fopen(path, "w");
		if (fp == NULL)
		{
			perror("fopen");
			exit(EXIT_FAILURE);
		}
		fclose(fp);
	}
}

int main(int argc, char *argv[])
{
	if (argc != 2) {
		printf("Usage: ./a.out <file_path>\n");
		return EXIT_FAILURE;
	}
	char *path = argv[1];
	char abs_path[4096];
	if (path[0] != '/')
	{
		char cwd[4096];
		if (getcwd(cwd, sizeof(cwd)) == NULL)
		{
			perror("getcwd");
			return EXIT_FAILURE;
		}
		snprintf(abs_path, sizeof(abs_path), "%s/%s", cwd, path);
	}
	else
	{
		strncpy(abs_path, path, sizeof(abs_path));
	}
	execute_touch(abs_path);
	return EXIT_SUCCESS;
}
