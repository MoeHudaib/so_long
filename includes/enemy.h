/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad <mohammad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 02:02:10 by mohammad          #+#    #+#             */
/*   Updated: 2025/09/20 02:02:11 by mohammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENEMY_H
#define ENEMY_H

#include "point.h"

typedef struct s_enemy
{
    t_point position;
    int alive;
    int direction;
}	t_enemy;

#endif