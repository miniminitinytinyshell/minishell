/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:35:56 by jaeblee           #+#    #+#             */
/*   Updated: 2024/03/27 16:38:29 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"
#include "libft.h"

#include <string.h> // Temp

void	check_leaks(void)
{
	system("leaks minishell");
}

void	display_tree(t_tree *tree, char *indent, int check)
{
	char	*tree_type[] = {"r_cmd", "RDR", "CMD", "STD", "CPD"};

	if (tree == NULL)
		return;
	printf("%s", indent);
	if (check)
	{
		printf("└─");
		strcat(indent, "  ");
	}
	else
	{
		printf("├─");
		strcat(indent, "| ");
	}
	printf("%s", tree_type[tree->type]);
	if (tree->oper)
		printf(": %s\n", tree->oper);
	else if (tree->data)
	{
		printf(": ");
		for (int i = 0; tree->data[i]; i++)
		{
			printf("%s", tree->data[i]);
			if (tree->data[i + 1])
				printf(", ");
		}
		printf("\n");
	}
	else
		printf("\n");
	if (tree->left && tree->right)
	{
		display_tree(tree->left, indent, 0);
		display_tree(tree->right, indent, 1);
	}
	else
	{
		display_tree(tree->left, indent, 1);
		display_tree(tree->right, indent, 1);
	}
	indent[strlen(indent) - 2] = '\0';
}

char	**dup_envp(char **envp)
{
	int		i;
	char	**temp;

	i = 0;
	while (envp[i])
		i++;
	temp = (char **)malloc(sizeof(char *) * (i + 1));
	if (!temp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		temp[i] = ft_strdup(envp[i]);
		i++;
	}
	return (temp);
}

int	main(int argc, char **argv, char **envp)
{
	char	*cmd;
	char	*token_type[] = {"word", "sep", "con_op", "rdr_op"};
	char	indent[1024] = "";
	char	**env;
	t_token *token;
	t_token	*tmp_token;
	t_tree	*tree;
	t_tree	*tmp_tree;

	env = dup_envp(envp);
	while (1)
	{
		cmd = readline("this is prompt : ");
		token = NULL;
		tokenizer(&token, cmd);
		if (!token)
			printf("#### SYNTAX ERROR | token ####\n");
		else
		{
			printf("%7s  %18s\n", "type", "data");
			printf("-------  ------------------------------------------\n");
			tmp_token = token;
			while (tmp_token)
			{
				printf("%-7s  %s\n", token_type[tmp_token->group], tmp_token->data);
				tmp_token = tmp_token->next;
			}
			tree = init_tree();
			printf("\n--------------------------tree-----------------------\n");
			if (check_cpd_cmd(&tree, token) == 0)
				printf("#### SYNTAX ERROR | tree ####\n");
			else
			{
				if (expand_tree(&tree, env) == 0)
					printf("#### CMD/FILE ERROR | tree ####\n");
				else
				{
					tmp_tree = tree;
					display_tree(tmp_tree, indent, 1);
				}
			}
			free_tree(tree);
		}
		free(cmd);
		cmd = NULL;
		// check_leaks();
	}
	argc = 0;
	argv = NULL;
	envp = NULL;
	return (0);
}
