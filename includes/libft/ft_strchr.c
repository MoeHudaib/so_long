/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhdeeb <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 12:50:42 by mhdeeb            #+#    #+#             */
/*   Updated: 2025/08/10 12:51:08 by mhdeeb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

char	*ft_strchr(const char *str, char c)
{
	const char	*a;

	a = str;
	while (*a)
	{
		if (*a == c)
			return ((char *)a);
		a++;
	}
	if (c == 0)
		return ((char *)a);
	return (NULL);
}
