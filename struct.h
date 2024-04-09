/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:10:29 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/09 14:24:48 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# define T_WORD 0
# define T_OPER 1

# define EXIT_SIGNAL 130

typedef enum e_token_group
{
	word = 0,
	sep,
	con,
	rdr,
}	t_token_group;
// sep (, )
// con_op |, ||, &&
// rer_op <, <<, >, >>

// typedef enum e_token_type
// {
// 	word = 0,
// 	left_par,
// 	right_par,
// 	pipe_op,
// 	logic_or,
// 	logic_and,
// 	in_trunc,
// 	out_trunc,
// 	here_doc,
// 	out_append,
// }	t_token_type;

typedef struct s_token
{
	t_token_group	group;
	char			*data;
	struct s_token	*next;
}	t_token;
// token type macro
// 실제 확장은 확장단계

typedef enum e_parse_type
{
	rdr_cmd = 0,
	redirects,
	simple_cmd,
	standard_cmd,
	compound_cmd,
}	t_parse_type;

typedef struct s_tree
{
	char			*oper;
	char			**data;
	t_parse_type	type;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;
// data[0] origin;
// data: with_expansion;

typedef struct s_envp
{
	int		max_cnt;
	int		curr_cnt;
	char	**data;
}	t_envp;

#endif