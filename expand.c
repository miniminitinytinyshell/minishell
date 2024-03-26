/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:59:26 by jaeblee           #+#    #+#             */
/*   Updated: 2024/03/26 18:07:05 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

static int	expand_rdr(t_tree **tree)
{
	int		fd;
	t_tree	*rdr;

	fd = 0;
	rdr = (*tree)->left;
	if (ft_strncmp(rdr->left->data, "<", 2) == 0)
	{
		fd = open(rdr->right->data, O_RDONLY);
		if (fd < 0)
			return (0);
	}
	if ((*tree)->right)
		if (expand_rdr(&(*tree)->right) == 0)
			return (0);
	return (1);
}

static int	find_bulitin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	else
		return (0);
}

static int	expand_cmd(t_tree **tree, char **path)
{
	char	*cmd;

	cmd = (*tree)->left->data;
	if (access(cmd, F_OK) != 0)
	{
		if (find_bulitin(cmd) == 0)
			(*tree)->left->data = get_cmd_path(cmd, path);
		if ((*tree)->left->data == NULL)
			return (0);
	}
	return (1);
}

int	expand_tree(t_tree **tree, char **path)
{
	if ((*tree)->type == standard_cmd)
	{
		if ((*tree)->left)
			if (expand_rdr(&(*tree)->left) == 0)
				return (0);
		if ((*tree)->right)
			if (expand_cmd(&(*tree)->right, path) == 0)
				return (0);
	}
	else
	{
		if ((*tree)->left)
			if (expand_tree(&(*tree)->left, path) == 0)
				return (0);
		if ((*tree)->right)
			if (expand_tree(&(*tree)->right, path) == 0)
				return (0);
	}
	return (1);
}
