/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:35:56 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/02 14:19:07 by jaeblee          ###   ########.fr       */
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
	temp[i] = NULL;
	return (temp);
}

int	check_cmd(char *cmd)
{
	while (*cmd == ' ')
		cmd++;
	if (!(*cmd))
		return (-1);
	else
		return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int		status;
	char	*cmd;
	char	indent[1024] = "";
	char	**env;
	t_token *token;
	// char	*token_type[] = {"word", "sep", "con_op", "rdr_op"};
	// t_token	*tmp_token;
	t_tree	*tree;
	t_tree	*tmp_tree;

	if (argc > 2)
		return (0);
	status = 0;
	for (int i = 0; argv[i]; i++)
		printf("%s\n", argv[i]);
	env = dup_envp(envp);
	while (1)
	{
		cmd = readline("this is prompt : ");
		if (check_cmd(cmd) < 0)
			continue ;
		token = NULL;
		tokenizer(&token, cmd);
		if (!token)
			printf("#### SYNTAX ERROR | token ####\n");
		else
		{
			// printf("%7s  %18s\n", "type", "data");
			// printf("-------  ------------------------------------------\n");
			// tmp_token = token;
			// while (tmp_token)
			// {
			// 	printf("%-7s  %s\n", token_type[tmp_token->group], tmp_token->data);
			// 	tmp_token = tmp_token->next;
			// }
			tree = init_tree();
			printf("\n--------------------------tree-----------------------\n");
			if (check_pipe(&tree, token) != 0)
			{
				tmp_tree = tree;
				display_tree(tmp_tree, indent, 1);
				// execute_cpd_cmd(&tree, env, &status);
			}
			free_tree(tree);
		}
		free(cmd);
		cmd = NULL;
		// check_leaks();
	}
	return (0);
}
