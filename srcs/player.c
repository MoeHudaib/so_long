/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad <mohammad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 02:01:29 by mohammad          #+#    #+#             */
/*   Updated: 2025/09/20 02:01:30 by mohammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"
#include "input.h"
#include "game.h"

t_player	init_player(t_point point, int health)
{
    t_player    player;

    player.position = point;
    player.health = health;
    player.steps = 0;
    player.collectibles = 0;
    return (player);
}
