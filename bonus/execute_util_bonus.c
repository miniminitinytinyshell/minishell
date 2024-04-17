/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_util_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:37:07 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/17 15:02:46 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_bonus.h"
#include "function_bonus.h"

void	set_status(int *status)
{
	if (WIFSIGNALED(*status))
	{
		*status = 128 + WTERMSIG(*status);
		if (*status == 131)
			ft_putstr_fd("Quit: 3", STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	else
		*status = WEXITSTATUS(*status);
}

int	open_file(t_tree *tree, int *file_in, int *file_out)
{
	if (!tree)
		return (0);
	if (ft_strncmp(tree->left->data[0], "<", 1) == 0)
	{
		if (*file_in > 0)
			close(*file_in);
		*file_in = open(tree->left->data[1], O_RDONLY);
	}
	else
	{
		if (*file_out > 0)
			close(*file_out);
		if (ft_strncmp(tree->left->data[0], ">", 2) == 0)
			*file_out = open(tree->left->data[1], \
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			*file_out = open(tree->left->data[1], \
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	if (*file_in < 0)
		return (error_with_str(tree->left->data[1], 0));
	else if (*file_out < 0)
		return (error_with_str(tree->left->data[1], 0));
	else
		return (open_file(tree->right, file_in, file_out));
}

char	*check_file(char *file)
{
	struct stat	file_stat;

	if (ft_strncmp(file, "/", 1) == 0 || ft_strncmp(file, "./", 2) == 0)
	{
		if (stat(file, &file_stat) == 0)
		{
			if (S_ISDIR(file_stat.st_mode))
				exit(error_with_str(file, IS_DIR));
		}
		else
			error_syscall();
		if (access(file, X_OK) != 0)
			exit(error_with_str(file, 0) + 125);
	}
	else
		return (NULL);
	return (file);
}