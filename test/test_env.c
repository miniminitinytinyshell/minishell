/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:48:57 by jaeblee           #+#    #+#             */
/*   Updated: 2024/03/27 19:09:04 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char *name;
	char *value;
	
	name = "PWD";
	value = getenv(name);
	if (value == NULL)
		printf("'%s'를 찾을 수 없습니다.\n", name);
	else
		printf("%s=%s\n", name, value);
	return 0;
}
