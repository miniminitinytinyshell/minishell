/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:48:57 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/06 19:08:45 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/errno.h>

int main(int argc, char *argv[])
{
	char *name;
	char *value;

	name = "HOME=";
	value = getenv("=");
	if (!value)
		printf("%s\n", strerror(errno));
	else
		printf("%s=%s\n", name, value);
	return 0;
}
