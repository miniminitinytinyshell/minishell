/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:35:56 by jaeblee           #+#    #+#             */
/*   Updated: 2024/03/23 20:51:10 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"
#include "libft.h"

#include <string.h> // Temp

// int	proc_cmd(char *cmd)
// {
// 	split_token();
// }

// void	print_tree(t_tree *tree)
// {
// 	char	*tree_type[] = {"name", "args", "rdr_op", "redirects", "simple_cmd", "standard_cmd", "compound_cmd"};

// 	if (tree->data != name)
// 		printf("%s: %s\n", tree_type[tree->type], tree->data);
// 	else
// 		printf("%s\n", tree_type[tree->type]);
// 	if (tree->left)
// 		print_tree(tree->left);
// 	if (tree->right)
// 		print_tree(tree->right);
// }

void	check_leaks(void)
{
	system("leaks minishell");
}

void	display_tree(t_tree *tree, char *indent, int check)
{
	char	*tree_type[] = {"name", "args", "oper", "RDR", "CMD", "STD", "CPD"};

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
	if (tree->data == NULL)
		printf("\n");
	else
		printf(": %s\n", tree->data);
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

int	main(void)
{
	char	*cmd;
	t_token *token;
	t_tree	*tree;
	char	*token_type[] = {"word", "sep", "con_op", "rdr_op"};
	t_token	*tmp_token;
	t_tree	*tmp_tree;
	char	indent[1024] = "";
	// bool	token_check;
	
	atexit(check_leaks);
	while (1)
	{
		cmd = readline("this is prompt : ");
		if (strcmp(cmd, "exit") == 0)
		{
			printf("exit!\n");
			break;
		}
		else
		{
			token = NULL;
			tokenizer(&token, cmd);
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
				printf("####SYNTAX ERROR####\n");
			else
			{
				tmp_tree = tree;
				display_tree(tmp_tree, indent, 1);
				//print_tree(tmp_tree);
			}
			free_tree(tree);
			// token_clear(&token);
		}
		free(cmd);
		cmd = NULL;
	}
	return (0);
}
