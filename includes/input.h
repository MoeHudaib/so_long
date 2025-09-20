/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad <mohammad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 02:01:56 by mohammad          #+#    #+#             */
/*   Updated: 2025/09/20 02:01:57 by mohammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include <stddef.h>

/* forward */
typedef struct s_game t_game;


// int		loop_hook(void *param);

/* Default keycodes (adjust for platform) */
typedef enum e_key
{
    KEY_W = 119,
    KEY_A = 97,
    KEY_S = 115,
    KEY_D = 100,
    KEY_ESC = 65307
} t_key;

#endif
