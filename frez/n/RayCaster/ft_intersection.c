/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intersection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 21:58:25 by bouhammo          #+#    #+#             */
/*   Updated: 2024/12/24 20:21:00 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../cub.h"

void drawing_line(t_start *var , int x0, int y0, int x1, int y1)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        if (x0 < 0 || y0 < 0 || x0 >= var->move->width_x || y0 >= var->move->height_y)
            return;
        ft_put_pixel_color(var, x0, y0, 0xFFFFFF);
        if (x0 == x1 && y0 == y1)
            break;
        
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

int check_uniq_rays(t_start *var, double x, double y)
{
    int  map_x ;
    int  map_y ;
    if (!var || !var->move || !var->map)
        return -1;
    if (x + 1 < 0 || x + 1 >= var->move->width_x || y + 1 < 0 || y + 1 >= var->move->height_y)
        return -1;
    x++;
    map_x = (int)(x / TILE_SIZE);
    map_y = (int)(y / TILE_SIZE);
    if (var->map[map_y][map_x] == '1')
        return 0;
    y++;
    map_x = (int)(x / TILE_SIZE);
    map_y = (int)(y / TILE_SIZE);
    if (var->map[map_y][map_x] == '1')
        return 0;
    return 1;
}

int check_is_wall(t_start *var, double x, double y)
{
    if (!var || !var->move || !var->map)
        return -1;

    if (x < 0 || x >= var->move->width_x || y < 0 || y >= var->move->height_y)
        return -1;

    int map_x = (int)(x / TILE_SIZE);
    int map_y = (int)(y / TILE_SIZE);

    if (map_x < 0 || map_x >= var->move->width_x / TILE_SIZE || map_y < 0 || map_y >= var->move->height_y / TILE_SIZE)
        return -1;

    if (var->map[map_y][map_x] == '1')
        return 0;
    if (check_uniq_rays(var, x, y) == 0)
        return 0;
    return 1;
}

void	 git_first_x_intersection(t_start *var)
{
    t_intersection  inter;

	if(is_looking_up(var->ray->ray_angle))
		inter.first_intersection_y = floor(var->move->coor_y / TILE_SIZE) * TILE_SIZE - 1;
	else if(is_looking_down(var->ray->ray_angle))
		inter.first_intersection_y = floor(var->move->coor_y / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
	
	inter.first_intersection_x = var->move->coor_x + (inter.first_intersection_y - var->move->coor_y) / ( tan(var->ray->ray_angle));
	inter.next_intersection_x = inter.first_intersection_x;
	inter.next_intersection_y = inter.first_intersection_y;

	if(is_looking_up(var->ray->ray_angle))
		inter.ya = -TILE_SIZE;
	else if(is_looking_down(var->ray->ray_angle))
		inter.ya = TILE_SIZE;
	
	inter.xa = inter.ya / tan(var->ray->ray_angle);
	while (check_is_wall(var, inter.next_intersection_x , inter.next_intersection_y) == 1)
	{
		inter.next_intersection_x += inter.xa;
		inter.next_intersection_y += inter.ya;
	}
	var->ray->x_inter_horizontal = inter.next_intersection_x;
	var->ray->y_inter_horizontal = inter.next_intersection_y;
}

void    git_first_y_intersection(t_start *var) 
{
    t_intersection  inter;

	if (is_looking_right(var->ray->ray_angle))
		inter.first_intersection_x = floor(var->move->coor_x / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
	else if (is_looking_left(var->ray->ray_angle))
		inter.first_intersection_x = floor(var->move->coor_x / TILE_SIZE) * TILE_SIZE - 1;
	
	inter.first_intersection_y = var->move->coor_y + (inter.first_intersection_x - var->move->coor_x) * tan(var->ray->ray_angle);
	inter.next_intersection_x = inter.first_intersection_x;
	inter.next_intersection_y = inter.first_intersection_y;

	if (is_looking_right(var->ray->ray_angle))
		inter.xa = TILE_SIZE;
	else if (is_looking_left(var->ray->ray_angle))
		inter.xa = -TILE_SIZE;
	
	inter.ya = inter.xa * tan(var->ray->ray_angle);
	while (check_is_wall(var, inter.next_intersection_x , inter.next_intersection_y) == 1)
	{
		inter.next_intersection_x += inter.xa;
		inter.next_intersection_y += inter.ya;
	}
	var->ray->x_inter_vertical = inter.next_intersection_x;
	var->ray->y_inter_vaertical = inter.next_intersection_y;
}
