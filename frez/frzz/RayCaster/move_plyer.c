/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_plyer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 19:31:31 by bouhammo          #+#    #+#             */
/*   Updated: 2025/01/11 13:26:17 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void ft_put_pixel_color(t_start *var, double x, double y , int color)
{
    if (x >= 0 && x < var->move->width_x && y >= 0 && y < var->move->height_y)
        mlx_put_pixel(var->img, x, y,   color);
}


int check_is_wall_1(t_start *var, double index_x , double index_y)
{
    if (index_x < 0 || index_x >= var->move->width_x || index_y < 0 || index_y >= var->move->height_y)
        return 0;

    int x_map = index_x;
    int y_map = index_y;

	int y = y_map;
	while (y  < y_map + var->offset  )
	{
		int x = x_map;
		while (x < x_map + var->offset  )
		{
            int map_x = (int)(x / TILE_SIZE);
            int map_y = (int)(y / TILE_SIZE);
            if (var->map[map_y][map_x] == '1')
                return 0;
			x++;
		}
		y++;
	}
    int map_x = (int)(index_x / TILE_SIZE);
    int map_y = (int)(index_y / TILE_SIZE);
    if (var->map[map_y][map_x] == '1')
        return 0;
    return 1;
}

void step_move(mlx_key_data_t keydata, t_start *var)
{
    double move_x = 0.0;
    double move_y = 0.0;

    if (keydata.key == MLX_KEY_A)
        move_y -= PLAYER_SPEED;
    else if (keydata.key == MLX_KEY_D)
        move_y += PLAYER_SPEED;
    if (keydata.key == MLX_KEY_S)
        move_x -= PLAYER_SPEED;
    else if (keydata.key == MLX_KEY_W)
        move_x += PLAYER_SPEED;

    double angle = var->draw->angle;
    double rotated_x = (move_x * cos(angle)) - (move_y * sin(angle));
    double rotated_y = (move_x * sin(angle)) + (move_y * cos(angle));

    if (check_is_wall_1(var, var->move->coor_x + rotated_x, var->move->coor_y + rotated_y) == 0 )//|| check_player_in_map(var, var->move->coor_x , var->move->coor_y))
        return;
    var->move->coor_x += rotated_x;
    var->move->coor_y += rotated_y;
}


void move_player(mlx_key_data_t keydata, t_start *var)
{
    step_move(keydata, var);

    mlx_delete_image(var->mlx, var->img);
    print_pixel(var);
    print_pixel_player(var);
    fix_rays(keydata, var);
}
