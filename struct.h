/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:10:29 by jaeblee           #+#    #+#             */
/*   Updated: 2024/04/09 16:04:05 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# define T_WORD 0
# define T_OPER 1

typedef struct s_envp
{
	int		max_cnt;
	int		curr_cnt;
	char	**data;
}	t_envp;

typedef enum e_token_group
{
	word = 0,
	sep,
	con,
	rdr,
}	t_token_group;

typedef struct s_token
{
	t_token_group	group;
	char			*data;
	struct s_token	*next;
}	t_token;

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

#endif