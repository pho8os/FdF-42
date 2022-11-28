/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absaid <absaid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 07:26:43 by absaid            #+#    #+#             */
/*   Updated: 2022/10/19 14:49:02 by absaid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	srcsize;
	size_t	i;

	i = -1;
	srcsize = ft_strlen(src);
	if (!dstsize)
		return (srcsize);
	while (src[++i] && i < dstsize - 1)
		*(dst + i) = *(src + i);
	*(dst + i) = '\0';
	return (srcsize);
}
