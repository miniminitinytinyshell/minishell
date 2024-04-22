/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:33:23 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/22 13:39:22 by jaeblee          ###   ########.fr       */
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
	if (!env)
		error_syscall();
	free(temp);
	return (env);
}

char	*proc_envp(char *word, char **envp, int status)
{
	int		i;
	char	*result;

	i = 0;
	result = NULL;
	while (word[i])
	{
		if (word[i] == '$')
			result = strjoin_free(result, get_envp(word, envp, &i, status));
		else
		{
			result = strjoin_char(result, word[i]);
			i++;
		}
	}
	return (result);
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
			while (token)
			{
				data = table_join(data, token->data);
				token = token->next;
			}
			temp = free_null(temp);
			token_clear(&token); // token->next 때문에 제대로 free 안 됨
		}
		else
			data = table_join(data, ft_strdup((*tree)->data[i]));
		i++;
	}
	return (data);
}
