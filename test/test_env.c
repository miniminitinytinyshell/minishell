/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:48:57 by jaeblee           #+#    #+#             */
/*   Updated: 2024/03/28 08:39:45 by hyeunkim         ###   ########.fr       */
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
