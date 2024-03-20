/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 05:24:26 by hyeunkim          #+#    #+#             */
/*   Updated: 2023/10/15 18:48:22 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *str1, char const *str2)
{
	char	*result;
	size_t	len_total;

	len_total = ft_strlen(str1) + ft_strlen(str2) + 1;
	result = ft_calloc(len_total, sizeof(char));
	if (!result)
		return (NULL);
	ft_strlcpy(result, (char *)str1, ft_strlen(str1) + 1);
	ft_strlcat(result, (char *)str2, len_total);
	return (result);
}
