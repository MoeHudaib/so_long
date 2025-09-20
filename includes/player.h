/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad <mohammad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 02:01:47 by mohammad          #+#    #+#             */
/*   Updated: 2025/09/20 17:02:00 by mohammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "point.h"
# include "libft/libft.h"

typedef struct s_player
{
	t_point	position;
	int		steps;
	int		collectibles;
	int		health;
	int		last_movement;
}	t_player;

typedef enum e_movement_type
{
	UP = 888,
	DOWN = 777,
	LEFT = 666,
	RIGHT = 555
}	t_movement_type;

t_player	init_player(t_point point, int health);

#endif
