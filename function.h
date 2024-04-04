/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:39:56 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/04 15:20:05 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_H
# define FUNCTION_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include <stdbool.h>
# include <sys/errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>

# include "libft.h"

// TOKENIZE
// t_token_type	get_token_type(char *data, int len);
int				token_len(char *str);
void			tokenizer(t_token **token, char *str);

// TOKEN UTIL
void			token_add_back(t_token **token, t_token *new);
int				token_clear(t_token **token);
t_token			*token_free(t_token *token);
t_token			*token_new(char *data_start, int len, t_token_group group);

// TREE
int				check_pipe(t_tree **tree, t_token *token);
int				check_cpd_cmd(t_tree **tree, t_token *token);
int				check_std_cmd(t_tree **tree, t_token *token);
int				check_smp_cmd(t_tree **tree, t_token *token);
int				check_redirect(t_tree **tree, t_token *token);
int				div_std_cmd(t_token **left, t_token **right);

// TREE Utils
int				skip_sep(t_token **token);
int				get_token_size(t_token *token);
t_tree			*init_tree(void);
t_tree			*free_tree(t_tree *tree);
t_token			*erase_pr(t_token *token);

// EXPAND
int				expand_tree(t_tree **tree, char **envp, int status);

// EXPAND_Utils
char			*find_env(char *aim, char **envp);
char			**get_path(char **envp);
char			*get_cmd_path(char *cmd, char **path);

// ENV to list && to arr
char			**get_envp_arr(t_env *head);
t_env			*get_envp_list(char **envp);

// ENVP_Utils
void			add_env_back(t_env **head, t_env *new);
void			clear_env_list(t_env **head);

// BUILTIN
int				builtin_echo(char **args);
int				builtin_cd(char **args, char **envp);

// EXECUTE
void			execute_rdr(t_tree *tree);
void			execute_pipe(t_tree **tree, char **envp, int *status);
void			execute_pipe_cmd(t_tree **tree, char **envp, int *status);
void			execute_std_cmd(t_tree **tree, char **envp, int *status);
void			execute_cpd_cmd(t_tree **tree, char **envp, int *status);
int				find_builtin(t_tree *tree, char **envp, int *status);

// HERE_DOC
void			here_doc(char *end, int *file_in);

// STRING
char			*strjoin_char(char *str, char c);
char			*strjoin_free(char *str1, char *str2);

// ERROR
int				error_malloc(void);
int				error_syntax(char *str, t_token **token, int flag);
int				error_cmd_not_found(char *cmd);
int				error_no_file(char *cmd);
void			error_fork(void);
void			error_pipe(void);
void			error_cd(char *path);

// FREE
char			**free_tab(char **temp);

#endif