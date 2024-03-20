/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:10:29 by jaeblee           #+#    #+#             */
/*   Updated: 2024/03/20 13:41:14 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# define T_WORD 0
# define T_OPER 1

typedef enum e_token_type
{
	word = 1,
	sep,
	op,
}	t_token_type;

typedef struct s_token
{
	int		type;
	char	*data;
}	t_token;
// token type macro
// $같은 경우는 tree 만드는 과정에서 token type 변경
// 실제 확장은 확장단계

typedef enum e_parse_type
{
	name = 0,
	args,
	simple_cmd,
	standard_cmd,
	compound_cmd,
	redirects,
	io_redirect,
}	t_parse_type;

typedef struct s_tree
{
	int				type;
	char			*data[2];
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;
// data[0] origin;
// data[1] with_expansion;
#endif