/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad <mohammad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 02:29:38 by mohammad          #+#    #+#             */
/*   Updated: 2025/08/13 02:29:39 by mohammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_handle_specifier(char spec, va_list args)
{
	if (spec == '%')
		return (write(1, "%", 1));
	else if (spec == 'd' || spec == 'i')
		return (ft_printnbr(va_arg(args, int)));
	else if (spec == 'u')
		return (ft_printunbr(va_arg(args, unsigned int)));
	else if (spec == 's')
		return (ft_printstr(va_arg(args, char *)));
	else if (spec == 'c')
		return (write(1, &(char){va_arg(args, int)}, 1));
	else if (spec == 'x')
		return (ft_inttohexalow(va_arg(args, unsigned int)));
	else if (spec == 'X')
		return (ft_inttohexaup(va_arg(args, unsigned int)));
	else if (spec == 'p')
		return (ft_printptr(va_arg(args, void *)));
	else
		return (write(1, &spec, 1));
}

static void	ft_iniset(char *str)
{
	str[0] = 'p';
	str[1] = '%';
	str[2] = 'd';
	str[3] = 'i';
	str[4] = 'u';
	str[5] = 'x';
	str[6] = 'X';
	str[7] = 'c';
	str[8] = 's';
	str[9] = '\0';
}

static int	ft_isinset(int x)
{
	char	spec;
	int		i;
	char	set[9];

	spec = (unsigned char)x;
	ft_iniset(set);
	i = 0;
	while (i < 9)
	{
		if (set[i] == spec)
			return (1);
		i++;
	}
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		counter;

	i = 0;
	counter = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%' && ft_isinset(format[i + 1]))
		{
			counter += ft_handle_specifier(format[i + 1], args);
			i += 2;
		}
		else
		{
			counter += write(1, &format[i], 1);
			i++;
		}
	}
	va_end(args);
	return (counter);
}
