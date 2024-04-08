/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:30:27 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/08 13:31:19 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/errno.h>
#include <string.h>

int	main(void)
{
	char	pwd[1024];
	char	*pwd2;
	int		n;

	// if (getcwd(pwd, sizeof(pwd)) != NULL)
	// 	printf("%s\n", pwd);
	// chdir("..");
	// if (getcwd(pwd, sizeof(pwd)) != NULL)
	// 	printf("%s\n", pwd);
	pwd2 = getcwd(NULL, 0);
	printf("%s\n", pwd2);
	free(pwd2);
	n = chdir(NULL);
	pwd2 = getcwd(NULL, 0);
	printf("%s | %d, %s\n", strerror(errno), n, pwd2);
	free(pwd2);
	return (0);
}
