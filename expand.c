/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:59:26 by jaeblee           #+#    #+#             */
/*   Updated: 2024/03/27 16:38:11 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

static char	*find_env(char *word, char **envp)
{
	int		i;
	char	*temp;
	char	*env;

	i = 0;
	temp = word;
	while (*temp && *temp != '$')
		temp++;
	if (*temp == '$')
	{
		*temp = '\0';
		temp++;
		while (envp[i])
		{
			if (ft_strncmp(temp, envp[i], ft_strlen(temp)) == 0)
			{
				temp = ft_strdup(&envp[i][ft_strlen(temp) + 1]);
				break ;
			}
			i++;
		}
		if (!envp[i])
			temp = ft_strdup("");
		env = ft_strjoin(word, temp);
		free(word);
		free(temp);
		return (env);
	}
	return (word);
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

static int	expand_rdr(t_tree **tree, char **envp)
{
	int		fd;
	t_tree	*rdr;

	fd = 0;
	rdr = (*tree)->left;
	rdr->data[1] = find_env((*tree)->left->data[1], envp);
	if (ft_strncmp(rdr->data[0], "<", 2) == 0)
	{
		fd = open(rdr->data[1], O_RDONLY);
		if (fd < 0)
			return (0);
	}
	if ((*tree)->right)
		if (expand_rdr(&(*tree)->right, envp) == 0)
			return (0);
	return (1);
}

static int	expand_cmd(t_tree **tree, char **envp)
{
	int		i;
	char	*cmd;

	i = 0;
	while ((*tree)->data[i])
	{
		(*tree)->data[i] = find_env((*tree)->data[i], envp);
		i++;
	}
	cmd = (*tree)->data[0];
	if (access(cmd, F_OK) != 0)
	{
		if (find_bulitin(cmd) == 0)
			(*tree)->data[0] = get_cmd_path(cmd, get_path(envp));
		if ((*tree)->data[0] == NULL)
			return (0);
	}
	return (1);
}

int	expand_tree(t_tree **tree, char **envp)
{
	if ((*tree)->type == standard_cmd)
	{
		if ((*tree)->left)
			if (expand_rdr(&(*tree)->left, envp) == 0)
				return (0);
		if ((*tree)->right)
			if (expand_cmd(&(*tree)->right, envp) == 0)
				return (0);
	}
	else
	{
		if ((*tree)->left)
			if (expand_tree(&(*tree)->left, envp) == 0)
				return (0);
		if ((*tree)->right)
			if (expand_tree(&(*tree)->right, envp) == 0)
				return (0);
	}
	return (1);
}
