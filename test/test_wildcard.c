/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_wildcard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:13:39 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/04 17:56:52 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

int match(const char *pattern, const char *str)
{
	while (*pattern)
	{
		if (*pattern == '*')
		{
			while (*str)
			{
				if (match(pattern + 1, str))
					return 1;
				str++;
			}
			return match(pattern + 1, str);
		}
		else if (*pattern != '?' && *pattern != *str)
			return 0;
		pattern++;
		str++;
	}
	return !*str;
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <wildcard>\n", argv[0]);
		return 1;
	}

	DIR *dir;
	struct dirent *entry;
	char *wildcard = argv[1];

	if ((dir = opendir("..")) == NULL)
	{
		perror("opendir");
		return 1;
	}

	while ((entry = readdir(dir)) != NULL)
		if (entry->d_type == DT_REG && match(wildcard, entry->d_name))
			printf("%s\n", entry->d_name);

	closedir(dir);
	return 0;
}
