/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:33:23 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/23 11:38:01 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"

char	*get_envp(char *word, char **envp, int *i, int status)
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
		temp = strjoin_char(temp, word[(*i)++]);
	}
	if (!temp)
		env = ft_strdup("$");
	else
		env = find_env(temp, envp);
	free(temp);
	return (env);
}

char	*proc_envp(char *word, char **envp, int status)
{
	int		i;
	char	*temp;
	char	*result;

	i = 0;
	result = NULL;
	while (word[i])
	{
		if (word[i] == '$')
		{
			temp = get_envp(word, envp, &i, status);
			if (!temp)
				result = strjoin_free(result, ft_strdup(""));
			else
				result = strjoin_free(result, temp);
		}
		else
		{
			result = strjoin_char(result, word[i]);
			i++;
		}
	}
	return (result);
}

char	**add_token_to_table(char **tab, t_token *token)
{
	t_token	*curr;

	if (!token)
		error_syscall();
	while (token)
	{
		tab = table_join(tab, token->data);
		curr = token;
		token = token->next;
		free(curr);
	}
	return (tab);
}

char	**expand_envp(t_tree **tree, char **envp, int status)
{
	int		i;
	char	**data;
	char	*temp;
	t_token	*token;

	i = 0;
	data = NULL;
	while ((*tree)->data[i])
	{
		if (ft_strchr((*tree)->data[i], '$') && (*tree)->data[i][0] != '\'')
		{
			temp = proc_envp((*tree)->data[i], envp, status);
			token = tokenizer(temp);
			if (temp && !token)
				token = token_new("", 0);
			data = add_token_to_table(data, token);
			temp = free_null(temp);
		}
		else
			data = table_join(data, ft_strdup((*tree)->data[i]));
		i++;
	}
	free_tab((*tree)->data);
	return (data);
}
