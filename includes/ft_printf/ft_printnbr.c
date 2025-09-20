/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad <mohammad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 02:29:32 by mohammad          #+#    #+#             */
/*   Updated: 2025/08/13 02:29:33 by mohammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

static int	ft_putnbr_recursive(int n)
{
	int		count;
	char	d;

	count = 0;
	if (n == -2147483648)
		return (write(1, "-2147483648", 11));
	if (n < 0)
	{
		count += ft_putchar('-');
		n = -n;
	}
	if (n >= 10)
		count += ft_putnbr_recursive(n / 10);
	d = (n % 10) + '0';
	count += ft_putchar(d);
	return (count);
}

int	ft_printnbr(int n)
{
	return (ft_putnbr_recursive(n));
}
/*#include <unistd.h>

static int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

static int	ft_putnbr_recursive(long nb)
{
	int count = 0;
	char digit;

	if (nb < 0)
	{
		count += ft_putchar('-');
		nb = -nb;
	}
	if (nb >= 10)
		count += ft_putnbr_recursive(nb / 10);
	digit = (nb % 10) + '0';
	count += ft_putchar(digit);
	return count;
}

int	ft_printnbr(int n)
{
	return ft_putnbr_recursive((long)n);
}
*/
