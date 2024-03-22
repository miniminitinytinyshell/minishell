/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:39:56 by jaeblee           #+#    #+#             */
/*   Updated: 2024/03/22 14:13:05 by hyeunkim         ###   ########.fr       */
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

// TOKENIZE
t_token_type	set_token_type(char *data, int len);
int				token_len(char *str);
void			tokenizer(t_token **token, char *str);
// TOKEN UTIL
t_token			*token_new(char *data_start, int len, t_token_type type);
void			token_add_back(t_token **token, t_token *new);
void			token_clear(t_token **token);
// TOKEN CHECKER
// bool	check_parenthesis(t_token *token);
// bool	check_operator(t_token *token);
bool			check_token(t_token *token);
#endif