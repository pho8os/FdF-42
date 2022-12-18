/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hextodec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absaid <absaid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 10:38:07 by absaid            #+#    #+#             */
/*   Updated: 2022/12/18 14:46:31 by absaid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	hextodec(char *str)
{
	int	ret;
	int	hex;
	int	len;

	if (*str == '0' && (*(str + 1) == 'x' || *(str + 1) == 'X'))
		str += 2;
	len = ft_strlen(str);
	ret = 0;
	hex = 1;
	while (len-- && len <= 6)
	{
		if (ft_isdigit(str[len]))
			ret += (str[len] - 48) * hex;
		else if (str[len] >= 'A' && str[len] <= 'F')
			ret += (str[len] - 55) * hex;
		else if (str[len] >= 'a' && str[len] <= 'f')
			ret += (str[len] - 87) * hex;
		hex *= 16;
	}
	return (ret);
}
