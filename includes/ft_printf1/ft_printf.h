/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad <mohammad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 03:26:23 by mohammad          #+#    #+#             */
/*   Updated: 2025/09/19 19:02:49 by mohammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

/* Includes */
# include <unistd.h>
# include "../libft/libft.h"
# include <stdarg.h>
# include <stdlib.h>
# include <stdint.h>

/* Conversions */
int		ft_inttohexalow(unsigned int num);
int		ft_inttohexaup(unsigned int num);

/* Bytes Counting Functions */
int		ft_printnbr(int n);
int		ft_printstr(char *str);
int		ft_printunbr(unsigned int n);
int		ft_printptr(void *ptr);

/* My main Function */
int		ft_printf(const char *format, ...);

#endif
