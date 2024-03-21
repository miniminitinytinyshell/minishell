/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:10:29 by jaeblee           #+#    #+#             */
/*   Updated: 2024/03/21 18:26:26 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# define T_WORD 0
# define T_OPER 1

typedef enum e_token_type
{
	word = 0,
	sep,
	con_op,
	re_op,
}	t_token_type;
//sep: (, )
//con_op: |, ||, &&
//re_op: <, <<, >, >>

typedef struct s_token
{
	t_token_type	type;
	char			*data;
	struct s_token	*next;
}	t_token;
// token type macro
// $같은 경우는 tree 만드는 과정에서 token type 변경
// 실제 확장은 확장단계

typedef enum e_parse_type
{
	name = 0,
	args,
	rdr_op,
	redirects,
	simple_cmd,
	standard_cmd,
	compound_cmd,
}	t_parse_type;

typedef struct s_tree
{
	t_parse_type	type;
	char			*data;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;
// data[0] origin;
// data: with_expansion;
#endif