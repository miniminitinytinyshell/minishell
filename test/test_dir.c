/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:30:27 by jaeblee           #+#    #+#             */
/*   Updated: 2024/03/29 19:36:33 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int	main(void)
{
	char	pwd[1024];
	char	*pwd2;

	// if (getcwd(pwd, sizeof(pwd)) != NULL)
	// 	printf("%s\n", pwd);
	// chdir("..");
	// if (getcwd(pwd, sizeof(pwd)) != NULL)
	// 	printf("%s\n", pwd);
	pwd2 = getcwd(NULL, 0);
	printf("%s\n", pwd2);
	free(pwd2);
	chdir("..");
	pwd2 = getcwd(NULL, 0);
	printf("%s\n", pwd2);
	free(pwd2);
	int n =	chdir("/Users/hyeunkim/Downloads");
	pwd2 = getcwd(NULL, 0);
	printf("%d, %s\n", n, pwd2);
	free(pwd2);
	return (0);
}
