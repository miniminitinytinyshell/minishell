/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:39:56 by jaeblee           #+#    #+#             */
/*   Updated: 2024/03/22 16:01:55 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_H
# define FUNCTION_H

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
void			token_clear(t_token **token);

// TREE
int				check_cpd_cmd(t_tree **tree, t_token *token);
int				check_std_cmd(t_tree **tree, t_token *token);
int				check_smp_cmd(t_tree **tree, t_token *token);
int				check_redirect(t_tree **tree, t_token *token);

// TREE Utils
int				skip_sep(t_token **token);
t_tree			*init_tree(void);
t_token			*erase_pr(t_token *token);

#endif