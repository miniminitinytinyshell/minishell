/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:39:56 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/09 17:04:28 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_H
# define FUNCTION_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include <signal.h> //signal()
# include <string.h> //strerror()
# include <stdbool.h>
# include <termios.h> //tcgetattr()
# include <sys/errno.h>
# include <sys/wait.h>
# include <readline/readline.h> //readline()
# include <readline/history.h>

# include "libft.h"

// TEMP (마지막에 지워야 됨)
void	check_leaks(void);
void	display_tree(t_tree *tree, char *indent, int check);

// FREE
void	*free_null(void *temp);
char	**free_tab(char **temp);

// ERROR
void	error_syscall(void);
int		error_no_file(char *cmd);
int		error_many_args(char *cmd);
int		error_cmd_not_found(char *cmd);
int		error_syntax(char *str, t_token **token, int flag);

// STRING
char	*strjoin_char(char *str, char c);
char	*strjoin_free(char *str1, char *str2);
char	**table_dup(char **tab, int size);
char	**table_join(char **tab, char *data);

// HERE_DOC
void	here_doc(char *end, int *file_in);

// SIGNAL
void	term_print_on(void);
void	term_print_off(void);
void	handle_sigint(int signum);
void	handle_exit(int signum);
void	handle_set(int signum);

// SIGNAL SET
void	set_signal(void);
void	set_child_signal(void);
void	set_parent_signal(void);
void	set_heardoc_signal(void);
void	set_builtin_signal(void);

// TOKENIZE
int		token_len(char *str);
t_token	*tokenizer(char *str);

// TOKEN UTIL
void	token_add_back(t_token **token, t_token *new);
int		token_clear(t_token **token);
t_token	*token_free(t_token *token);
t_token	*token_new(char *data_start, int len);

// TREE
int		check_pipe(t_tree **tree, t_token *token);
int		check_cpd_cmd(t_tree **tree, t_token *token);
int		check_std_cmd(t_tree **tree, t_token *token);
int		check_smp_cmd(t_tree **tree, t_token *token);
int		check_redirect(t_tree **tree, t_token *token);
int		div_std_cmd(t_token **left, t_token **right);

// TREE Utils
int		skip_sep(t_token **token);
int		get_token_size(t_token *token);
t_tree	*init_tree(void);
t_tree	*free_tree(t_tree *tree);
t_token	*erase_pr(t_token *token);

// EXPAND
int		expand_tree(t_tree **tree, char **envp, int status);
void	expand_wildcard(t_tree **tree, int i);

// EXPAND_Utils
char	*find_env(char *aim, char **envp);
char	**get_path(t_envp *envp);
char	*get_cmd_path(char *cmd, char **path);

// BUILTIN
int		builtin_echo(char **args);
int		builtin_cd(char **args, t_envp *envp);
int		builtin_env(char **args, char **envp);
int		builtin_pwd(char **args);
int		builtin_exit(char **args);

// BUILTIN_Utils
int		swap_envp_data(char *key, char *value, t_envp *envp);
int		get_envp_idx(char *key, t_envp *envp);

// EXECUTE
void	execute_rdr(t_tree *tree);
void	execute_cmd(t_tree *tree, t_envp *envp);
void	execute_std_cmd(t_tree **tree, t_envp *envp, int *status);
void	execute_cpd_cmd(t_tree **tree, t_envp *envp, int *status);

// EXCUTE UTIL
void	set_status(int *status);
void	open_file(t_tree *tree, int *file_in, int *file_out);

// EXECUTE PIPE
void	execute_pipe(t_tree **tree, t_envp *envp, int *status);
void	execute_pipe_cmd(t_tree **tree, t_envp *envp, int *status);

// EXECUTE BUILTIN
int		find_builtin(t_tree *tree);
void	execute_builtin(t_tree *tree, t_envp *envp, int *status);

#endif