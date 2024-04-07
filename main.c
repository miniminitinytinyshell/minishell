/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:35:56 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/07 18:58:06 by jaeblee          ###   ########.fr       */
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

void	set_signal(void)
{
	term_print_off();
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

int	check_cmd(char *cmd)
{
	if (!cmd)
		exit(EXIT_SUCCESS);
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
	char	**env;
	t_tree	*tree;

	if (argc > 1)
		return (printf("usage: %s\n", argv[0]));
	set_signal();
	env = dup_envp(envp);
	while (1)
	{
		cmd = readline("minishell> ");
		if (check_cmd(cmd) < 0)
			continue ;
		tree = init_tree();
		if (check_pipe(&tree, tokenizer(cmd)) != 0)
			execute_cpd_cmd(&tree, env, &status);
		if (cmd)
			add_history(cmd);
		cmd = free_null(cmd);
		check_leaks();
	}
	return (0);
}
