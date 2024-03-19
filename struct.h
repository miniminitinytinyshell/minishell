/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeblee <jaeblee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:10:29 by jaeblee           #+#    #+#             */
/*   Updated: 2024/03/19 17:43:47 by jaeblee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# define T_WORD 0
# define T_OPER 1

typedef enum e_type
{
	cmd_line = 0,
	cmd,
}	t_type;

typedef struct s_token
{
	int		type;
	char	*data;
}	t_token;

typedef struct s_tree
{
	int				type;
	char			*data[2];
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

#endif