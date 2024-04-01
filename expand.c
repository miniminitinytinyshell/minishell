/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:59:26 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/01 14:00:43 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

static char	*expand_env(char *word, char **envp, int *i, int status)
{
	char	*env;
	char	*temp;

	*i += 1;
	env = NULL;
	temp = NULL;
	if (word[*i] == '?')
	{
		*i += 1;
		return (ft_itoa(status));
	}
	while (word[*i])
	{
		if (ft_isalnum(word[*i]) == 0 && word[*i] != '_')
			break ;
		temp = strjoin_char(temp, word[*i]);
		*i += 1;
	}
	if (!temp)
		env = ft_strdup("$");
	else
		env = find_env(temp, envp);
	free(temp);
	return (env);
}

static char	*expand_word(char *word, char **envp, int status)
{
	int		i;
	char	quote;
	char	*result;

	i = 0;
	quote = 0;
	result = NULL;
	while (word[i])
	{
		if (word[i] == '\'' || word[i] == '\"')
		{
			if (quote == 0)
				quote = word[i];
			else if (quote == word[i])
				quote = 0;
			else
				result = strjoin_char(result, word[i]);
			i++;
		}
		else if (quote != '\'' && word[i] == '$')
			result = strjoin_free(result, expand_env(word, envp, &i, status));
		else
			result = strjoin_char(result, word[i++]);
	}
	free(word);
	return (result);
}

static int	expand_rdr(t_tree **tree, char **envp, int status)
{
	int		fd;
	t_tree	*rdr;

	fd = 0;
	rdr = (*tree)->left;
	rdr->data[1] = expand_word(rdr->data[1], envp, status);
	if (ft_strncmp(rdr->data[0], "<", 2) == 0)
	{
		fd = open(rdr->data[1], O_RDONLY);
		if (fd < 0)
			return (0);
	}
	if ((*tree)->right)
		if (expand_rdr(&(*tree)->right, envp, status) == 0)
			return (0);
	return (1);
}

static int	expand_cmd(t_tree **tree, char **envp, int status)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	temp = NULL;
	while ((*tree)->data[i])
	{
		(*tree)->data[j] = expand_word((*tree)->data[i], envp, status);
		if ((*tree)->data[j])
			j++;
		i++;
	}
	(*tree)->data[j] = NULL;
	return (1);
}

int	expand_tree(t_tree **tree, char **envp, int status)
{
	if ((*tree)->left)
		if (expand_rdr(&(*tree)->left, envp, status) == 0)
			return (0);
	if ((*tree)->right)
		if (expand_cmd(&(*tree)->right, envp, status) == 0)
			return (0);
	return (1);
}
