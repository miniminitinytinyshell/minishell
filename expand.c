/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:59:26 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/16 13:58:19 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

char	*expand_env(char *word, char **envp, int *i, int status)
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

char	*expand_word(char *word, char **envp, int status)
{
	int		i;
	char	quote;
	char	*result;

	i = 0;
	quote = 0;
	result = NULL;
	if (word[0] == '\'' || word[0] == '\"')
		if (word[0] == word[1])
			return (ft_strdup(""));
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
	return (result);
}

static int	expand_rdr(t_tree **tree, char **envp, int status)
{
	char	*file;
	t_tree	*rdr;

	rdr = (*tree)->left;
	file = expand_word(rdr->data[1], envp, status);
	free(rdr->data[1]);
	rdr->data[1] = file;
	if ((*tree)->right)
		expand_rdr(&(*tree)->right, envp, status);
	return (1);
}

static int	expand_cmd(t_tree **tree, char **envp, int status)
{
	int		i;
	char	**data;

	i = 1;
	while ((*tree)->data[i])
	{
		if (ft_strchr((*tree)->data[i], '*'))
			if ((*tree)->data[i][0] != '\"' && (*tree)->data[i][0] != '\'')
				expand_wildcard(tree, &i);
		i++;
	}
	i = 0;
	data = NULL;
	while ((*tree)->data[i])
	{
		data = table_join(data, expand_word((*tree)->data[i], envp, status));
		i++;
	}
	free_tab((*tree)->data);
	(*tree)->data = data;
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
