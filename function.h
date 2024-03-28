/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:39:56 by jaeblee           #+#    #+#             */
/*   Updated: 2024/03/28 19:07:43 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_H
# define FUNCTION_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "libft.h"

// TOKENIZE
// t_token_type	get_token_type(char *data, int len);
int				token_len(char *str);
void			tokenizer(t_token **token, char *str);

// TOKEN UTIL
t_token			*token_new(char *data_start, int len, t_token_group group);
void			token_add_back(t_token **token, t_token *new);
t_token			*token_free(t_token *token);
int				token_clear(t_token **token);

// TREE
int				div_std_cmd(t_token **left, t_token **right);
int				check_cpd_cmd(t_tree **tree, t_token *token);
int				check_std_cmd(t_tree **tree, t_token *token);
int				check_smp_cmd(t_tree **tree, t_token *token);
int				check_redirect(t_tree **tree, t_token *token);

// TREE Utils
int				skip_sep(t_token **token);
int				get_token_size(t_token *token);
t_tree			*init_tree(void);
t_tree			*free_tree(t_tree *tree);
t_token			*erase_pr(t_token *token);

// EXPAND
int				expand_tree(t_tree **tree, char **path, int status);

// EXPAND_Utils
int				find_bulitin(char *cmd);
char			*find_env(char *aim, char **envp);
char			**get_path(char **envp);
char			*get_cmd_path(char *cmd, char **path);

// BUILTIN
int	builtin_echo(char **args, char **envp);

// STRING
char			*strjoin_char(char *str, char c);
char			*strjoin_free(char *str1, char *str2);

// ERROR
int				error_malloc(t_token **token);
int				error_syntax(char *str, t_token **token);

// FREE
char			**free_tab(char **temp);

#endif