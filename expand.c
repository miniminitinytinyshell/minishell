/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:59:26 by jaeblee           #+#    #+#             */
/*   Updated: 2024/03/27 17:30:21 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

static char	*expand_env(char *word, char **envp)
{
	char	*temp;
	char	*env;

	temp = word;
	while (*temp && *temp != '$')
		temp++;
	if (*temp == '$')
	{
		*temp = '\0';
		temp++;
		while (*envp)
		{
			if (ft_strncmp(temp, *envp, ft_strlen(temp)) == 0)
			{
				if (*(*envp + ft_strlen(temp)) == '=')
				{
					temp = ft_strdup(*envp + ft_strlen(temp) + 1);
					break ;
				}
			}
			envp++;
		}
		if (!(*envp))
			temp = ft_strdup("");
		env = ft_strjoin(word, temp);
		free(word);
		free(temp);
		return (env);
	}
	return (word);
}

// static char	*expand_path(char *cmd, char **envp)
// {
// 	char	*pwd;
// 	char	*path;

// 	pwd = NULL;
// 	while (*envp)
// 	{
// 		if (ft_strncmp("PWD=", *envp, 4) == 0)
// 		{
// 			pwd = ft_strdup(*envp + 4);
// 			break ;
// 		}
// 		envp++;
// 	}
// 	if (!pwd)
// 		return (cmd);
// 	path = ft_strjoin(pwd, cmd);
// 	free(pwd);
// 	free(cmd);
// 	return (path);
// }

static int	expand_rdr(t_tree **tree, char **envp)
{
	int		fd;
	t_tree	*rdr;

	fd = 0;
	rdr = (*tree)->left;
	rdr->data[1] = expand_env((*tree)->left->data[1], envp);
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
	char	*temp;

	i = 0;
	temp = NULL;
	while ((*tree)->data[i])
	{
		(*tree)->data[i] = expand_env((*tree)->data[i], envp);
		i++;
	}
	if (find_bulitin((*tree)->data[0]) == 0)
	{
		// temp = expand_path((*tree)->data[0], envp);
		if (access((*tree)->data[0], O_RDONLY) != 0)
			(*tree)->data[0] = get_cmd_path((*tree)->data[0], get_path(envp));
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
