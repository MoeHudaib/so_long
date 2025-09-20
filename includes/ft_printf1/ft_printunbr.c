/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printunbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad <mohammad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 02:29:22 by mohammad          #+#    #+#             */
/*   Updated: 2025/08/13 02:29:23 by mohammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

static int	ft_putnbr_recursive(unsigned int n)
{
	int		count;
	char	d;

	count = 0;
	if (n >= 10)
		count += ft_putnbr_recursive(n / 10);
	d = (n % 10) + '0';
	count += ft_putchar(d);
	return (count);
}

int	ft_printunbr(unsigned int n)
{
	return (ft_putnbr_recursive(n));
}
