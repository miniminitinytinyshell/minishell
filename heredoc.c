/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:08:24 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/09 19:09:57 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

extern int	g_signum;

void	here_doc(char *eof, int fd)
{
	char	*read_line;

	while (1)
	{
		read_line = readline("heredoc> ");
		if (!read_line)
			break ;
		if (ft_strncmp(read_line, eof, ft_strlen(eof) + 1) == 0)
		{
			free(read_line);
			read_line = NULL;
			break ;
		}
		ft_putendl_fd(read_line, fd);
		read_line = free_null(read_line);
	}
	close(fd);
}

void	make_heardoc(t_tree **tree, int *name)
{
	int		fd;
	char	*path;

	path = NULL;
	if ((*tree)->type == rdr_cmd)
	{
		if (ft_strncmp((*tree)->data[0], "<<", 3) == 0)
		{
			path = ft_strjoin("/Users/jaeblee/goinfre/temp/tmp_", ft_itoa(*name));
			fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			here_doc((*tree)->data[1], fd);
			free((*tree)->data[1]);
			(*tree)->data[1] = path;
			*name += 1;
		}
	}
	else
	{
		if ((*tree)->left)
			make_heardoc(&(*tree)->left, name);
		if ((*tree)->right)
			make_heardoc(&(*tree)->right, name);
	}
}

void	traver_heardoc(t_tree **tree)
{
	int	name;

	name = 1;
	make_heardoc(tree, &name);
}
