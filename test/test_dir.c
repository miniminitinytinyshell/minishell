/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:30:27 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/09 17:45:30 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/errno.h>
#include <string.h>

int	main(void)
{
	char	*pwd;
	int		n;
	int		t;

	chdir("/Users/hyeunkim/42cursus/minishell/test/1/2/3");
	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
	scanf("%d\n", &n);
	n = 0;
	n = chdir("..");
	scanf("%d\n", &t);
	pwd = getcwd(NULL, 0);
	printf("%s(%d) | %d, %s\n", strerror(errno), errno, n, pwd);
	printf("access: %d\n", access(pwd, F_OK));
	printf("%s(%d) | %d, %s\n", strerror(errno), errno, n, pwd);
	free(pwd);
	scanf("%d\n", &n);
	return (0);
}
