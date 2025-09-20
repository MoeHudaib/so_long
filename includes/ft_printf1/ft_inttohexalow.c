/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inttohexalow.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad <mohammad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 02:30:18 by mohammad          #+#    #+#             */
/*   Updated: 2025/09/19 19:05:21 by mohammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putchar_fd1(char c, int fd)
{
	return (write(fd, &c, 1));
}

static char	*ft_reverse(char *str)
{
	int		start;
	int		end;
	char	temp;

	start = 0;
	end = ft_strlen(str) - 1;
	while (start < end)
	{
		temp = str[start];
		str[start] = str[end];
		str[end] = temp;
		start++;
		end--;
	}
	return (str);
}

static unsigned int	ft_hexlen(unsigned int x)
{
	unsigned int	len;

	len = 0;
	if (x == 0)
		return (1);
	while (x > 0)
	{
		len++;
		x /= 16;
	}
	return (len);
}

int	ft_inttohexalow(unsigned int num)
{
	char	*str;
	int		remainder;
	int		i;

	if (num == 0)
		return (ft_putchar_fd1('0', 1));
	str = malloc(ft_hexlen(num) + 1);
	if (!str)
		return (0);
	i = 0;
	while (num > 0)
	{
		remainder = num % 16;
		if (remainder < 10)
			str[i] = remainder + '0';
		else
			str[i] = (remainder - 10) + 'a';
		i++;
		num /= 16;
	}
	str[i] = '\0';
	write(1, ft_reverse(str), i);
	free(str);
	return (i);
}
