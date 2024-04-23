/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:59:26 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/23 12:08:46 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

char	*expand_word(char *word, char **envp, int status)
{
	int		i;
	char	quote;
	char	*result;

	i = 0;
	quote = 0;
	result = NULL;
	(void)envp;
	(void)status;
	if ((word[0] == '\'' || word[0] == '\"') && word[0] == word[1])
		return (ft_strdup(""));
	while (word[i])
	{
		if (word[i] == '\'' || word[i] == '\"')
		{
			expand_quote(word[i], &quote, &result);
			i++;
		}
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
	rdr->data = expand_envp(&rdr, envp, status);
	if (ft_strchr(rdr->data[1], '*'))
		if (rdr->data[1][0] != '\"' && rdr->data[1][0] != '\'')
			expand_wildcard(&rdr, 1);
	if (rdr->data[2] || rdr->data[1][0] == '\0')
	{
		ft_putendl_fd("minishell: ambiguous redirect", STDERR_FILENO);
		return (0);
	}
	file = expand_word(rdr->data[1], envp, status);
	if (!file)
		error_syscall();
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

	(*tree)->data = expand_envp(tree, envp, status);
	i = 0;
	while ((*tree)->data[i])
	{
		if (ft_strchr((*tree)->data[i], '*'))
			if ((*tree)->data[i][0] != '\"' && (*tree)->data[i][0] != '\'')
				expand_wildcard(tree, i);
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
			return (1);
	if ((*tree)->right)
		if (expand_cmd(&(*tree)->right, envp, status) == 0)
			return (1);
	return (0);
}
