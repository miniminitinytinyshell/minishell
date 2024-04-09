/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:37:07 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/09 14:39:03 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

void	set_status(int *status)
{
	if (WIFSIGNALED(*status))
		*status = EXIT_SIGNAL;
	else
		*status = WEXITSTATUS(*status);
}

void	open_file(t_tree *tree, int *file_in, int *file_out)
{
	if (!tree)
		return ;
	if (ft_strncmp(tree->left->data[0], "<", 1) == 0)
	{
		if (*file_in > 0)
			close(*file_in);
		if (ft_strncmp(tree->left->data[0], "<", 2) == 0)
			*file_in = open(tree->left->data[1], O_RDONLY);
		else
			here_doc(tree->left->data[1], file_in);
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
		error_no_file(tree->left->data[1]);
	open_file(tree->right, file_in, file_out);
}
