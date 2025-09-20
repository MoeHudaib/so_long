/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad <mohammad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 02:28:59 by mohammad          #+#    #+#             */
/*   Updated: 2025/08/13 02:29:03 by mohammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_reverse(char *str)
{
	int				start;
	int				end;
	unsigned char	temp;

	start = 0;
	end = ft_strlen(str) - 1;
	while (start < end)
	{
		temp = (unsigned char)str[start];
		str[start] = (unsigned char)str[end];
		str[end] = temp;
		++start;
		--end;
	}
	return (str);
}

static int	ft_putstr(const char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return (write(1, s, len));
}

static void	setbase(char *base1)
{
	int	i;

	i = 0;
	while (i < 16)
	{
		if (i < 10)
			base1[i] = i + '0';
		else
			base1[i] = (i - 10) + 'a';
		++i;
	}
	base1[i] = '\0';
}

static char	*ft_to_hex(uintptr_t n)
{
	char	*hex;
	char	base[17];
	int		i;

	i = 0;
	setbase(base);
	hex = malloc(17);
	if (!hex)
		return (NULL);
	if (n == 0)
		hex[i++] = '0';
	while (n)
	{
		hex[i++] = base[n % 16];
		n /= 16;
	}
	hex[i] = '\0';
	return (ft_reverse(hex));
}

int	ft_printptr(void *ptr)
{
	uintptr_t	address;
	char		*hexstr;
	int			count;

	if (!ptr)
		return (write(1, "(nil)", 5));
	address = (uintptr_t)ptr;
	count = 0;
	count += ft_putstr("0x");
	hexstr = ft_to_hex(address);
	if (!hexstr)
		return (0);
	count += ft_putstr(hexstr);
	free(hexstr);
	return (count);
}
