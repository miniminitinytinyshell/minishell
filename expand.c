/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:59:26 by jaeblee           #+#    #+#             */
/*   Updated: 2024/03/28 15:49:00 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

static char	*expand_env(char *result, char *word, int *i, char **envp)
{
	char	*env;
	char	*temp;

	*i += 1;
	env = NULL;
	temp = NULL;
	while (word[*i])
	{
		if (word[*i] < 'a' || word[*i] > 'z')
			if (word[*i] < 'A' || word[*i] > 'Z')
				if (word[*i] != '_')
					break ;
		temp = word_join(temp, word[*i]);
		*i += 1;
	}
	if (!temp)
	{
		env = ft_strjoin(result, "$");
		free(result);
	}
	else
		env = find_env(result, temp, envp);
	free(temp);
	return (env);
}

static char	*expand_word(char *word, char **envp)
{
	int		i;
	char	quote;
	char	*result;

	i = 0;
	quote = 0;
	result = ft_strdup("");
	while (word[i])
	{
		if (word[i] == '\'' || word[i] == '\"')
		{
			if (quote == 0)
				quote = word[i];
			else if (quote == word[i])
				quote = 0;
			else
				result = word_join(result, word[i]);
			i++;
		}
		else if (quote != '\'' && word[i] == '$')
			result = expand_env(result, word, &i, envp);
		else
			result = word_join(result, word[i++]);
	}
	return (result);
}

static int	expand_rdr(t_tree **tree, char **envp)
{
	int		fd;
	t_tree	*rdr;

	fd = 0;
	rdr = (*tree)->left;
	rdr->data[1] = expand_word(rdr->data[1], envp);
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
		(*tree)->data[i] = expand_word((*tree)->data[i], envp);
		i++;
	}
	if (find_bulitin((*tree)->data[0]) == 0)
	{
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
