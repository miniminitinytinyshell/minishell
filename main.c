/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:35:56 by jaeblee           #+#    #+#             */
/*   Updated: 2024/03/22 15:49:36 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "function.h"
#include "libft.h"

// int	proc_cmd(char *cmd)
// {
// 	split_token();
// }

void	print_tree(t_tree *tree)
{
	if (tree->left)
		print_tree(tree->left);
	else if (tree->right)
		print_tree(tree->right);
	else if (!(tree->left) && !(tree->right))
		printf("%s\n", tree->data);
}

int	main(void)
{
	char	*cmd;
	t_token *token;
	t_tree	*tree;
	char	*token_type[] = {"word", "sep", "con_op", "rdr_op"};
	t_token	*tmp_token;
	t_tree	*tmp_tree;
	// bool	token_check;
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
			if (check_cpd_cmd(&tree, token) == 0)
				printf("####SYNTAX ERROR####\n");
			else
			{
				tmp_tree = tree;
				print_tree(tmp_tree);
			}
			token_clear(&token);
		}
		free(cmd);
		cmd = NULL;
	}
	return (0);
}
