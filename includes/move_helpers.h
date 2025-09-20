/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_helpers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad <mohammad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 02:01:50 by mohammad          #+#    #+#             */
/*   Updated: 2025/09/20 02:01:51 by mohammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOVE_HELPERS_H
# define MOVE_HELPERS_H

# include "game.h"

typedef struct s_move_info
{
	t_minilibx	*data;
	int			old_x;
	int			old_y;
	int			new_x;
	int			new_y;
	int			movement_type;
}				t_move_info;

#endif