/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_plyer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 19:31:31 by bouhammo          #+#    #+#             */
/*   Updated: 2024/12/01 11:06:39 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"



void ft_put_pixel(t_start *var, double x, double y)
{

    if (x >= 0 && x < var->move->width_x && y >= 0 && y < var->move->height_y)
    {
        mlx_put_pixel(var->img, x, y, 0xFFFF00FF);
    }
}
int     check_is_valid(t_start *var)
{
     if (var->move == NULL || var->move->coor_x < 0 || var->move->coor_y < 0 ||
        var->move->coor_x >= var->move->width_x || var->move->coor_y >= var->move->height_y)
    {
        return 1;
    }

    return 0;
}

void       draw_line_dda(t_start *var)
{   
    if(check_is_valid(var) ==1)
        return ;
        
    var->draw->new_point_x = (var->move->coor_x / TILE_SIZE) +  (cos(var->draw->angle) * TILE_SIZE);
    var->draw->new_point_y = (var->move->coor_y / TILE_SIZE) +  (sin(var->draw->angle) * TILE_SIZE);
    double dx = var->draw->new_point_x  - (var->move->coor_x / TILE_SIZE);
    double dy = var->draw->new_point_y  - (var->move->coor_y / TILE_SIZE);

    double step=0;
    if( fabs(dx) >= fabs(dy))    
        step = fabs(dx);
    else   
        step = fabs(dy);
    if( step == 0)
        return ;        
    double x_inc = dx / step;
    double y_inc = dy / step;
    
    double x = var->move->coor_x + (var->offset / 2);
    double y = var->move->coor_y + (var->offset / 2);

    int i=0;
    while (i <= (step * 10)  )
    {
        ft_put_pixel(var , roundf(x) , roundf(y));
        x += x_inc;
        y += y_inc;
        i++;
    }
}


void move_player_up(t_start *var, int dx, int dy)
{

(void)dx;
(void)dy;
    double move_x = cos(var->draw->angle) * PLAYER_SPEED;
	double move_y = sin(var->draw->angle) * PLAYER_SPEED;

    int new_position_x = var->move->coor_x + move_x;
    int new_position_y = var->move->coor_y + move_y ;

    if (!check_player_in_map(var, new_position_x , new_position_y))
        return;

    var->move->coor_x += move_x ;
    var->move->coor_y += move_y ;
    mlx_delete_image(var->mlx, var->img);
    print_pixel(var);
    print_pixel_player(var);
    draw_line_dda(var);

}

void move_player_down(t_start *var, int dx, int dy)
{
(void)dx;
(void)dy;
    double move_x = -cos(var->draw->angle) * PLAYER_SPEED;
	double move_y = -sin(var->draw->angle) * PLAYER_SPEED;
    
    int new_position_x = var->move->coor_x + move_x;
    int new_position_y = var->move->coor_y + move_y;
    
    if (!check_player_in_map(var,  new_position_x, new_position_y ))
        return;

    var->move->coor_x += move_x ;
    var->move->coor_y += move_y ;
    mlx_delete_image(var->mlx, var->img);
    print_pixel(var);
    print_pixel_player(var);
    draw_line_dda(var);



}

void move_player_left(t_start *var, int dx, int dy)
{
(void)dx;
(void)dy;
    double move_x = sin(var->draw->angle) * PLAYER_SPEED;
	double move_y = -cos(var->draw->angle) * PLAYER_SPEED;
    
    int new_position_x = var->move->coor_x + move_x;
    int new_position_y = var->move->coor_y + move_y;
    
    if (!check_player_in_map(var, new_position_x, new_position_y ))
        return;

    var->move->coor_x += move_x ;
    var->move->coor_y += move_y ;
    // var->move->coor_y = new_position_y;

    mlx_delete_image(var->mlx, var->img);
    print_pixel(var);
    print_pixel_player(var);
    draw_line_dda(var);
}

void move_player_right(t_start *var, int dx, int dy)
{
(void)dx;
(void)dy;
    double move_x = -sin(var->draw->angle) * PLAYER_SPEED;
	double move_y = cos(var->draw->angle) * PLAYER_SPEED;
    
    int new_position_x = var->move->coor_x + move_x;
    int new_position_y = var->move->coor_y + move_y;
    
    if (!check_player_in_map(var, new_position_x, new_position_y ))
        return;

    var->move->coor_x += move_x ;
    var->move->coor_y += move_y ;

    mlx_delete_image(var->mlx, var->img);
    print_pixel(var);
    print_pixel_player(var);
    draw_line_dda(var);

}





















// void move_player_up(t_start *var, int dx, int dy)
// {
//     int new_position_x = var->move->coor_x + dx;
//     int new_position_y = var->move->coor_y + dy;

//     if (!check_player_in_map(var, new_position_x, new_position_y))
//         return;
//     var->move->coor_y = new_position_y;
//     mlx_delete_image(var->mlx, var->img);
//     print_pixel(var);
//     print_pixel_player(var);
//     draw_line_dda(var);

// }

// void move_player_down(t_start *var, int dx, int dy)
// {
//     int new_position_x = var->move->coor_x + dx;
//     int new_position_y = var->move->coor_y + dy;

//     if (!check_player_in_map(var, new_position_x, new_position_y))
//         return;

//     var->move->coor_y = new_position_y;
//     mlx_delete_image(var->mlx, var->img);
//     print_pixel(var);
//     print_pixel_player(var);
//     draw_line_dda(var);



// }

// void move_player_left(t_start *var, int dx, int dy)
// {
//     int new_position_x = var->move->coor_x + dx;
//     int new_position_y = var->move->coor_y + dy;

//     if (!check_player_in_map(var, new_position_x, new_position_y))
//         return;

//     var->move->coor_x = new_position_x;

//     mlx_delete_image(var->mlx, var->img);
//     print_pixel(var);
//     print_pixel_player(var);
//     draw_line_dda(var);
// }

// void move_player_right(t_start *var, int dx, int dy)
// {
//     int new_position_x = var->move->coor_x + dx;
//     int new_position_y = var->move->coor_y + dy;

//     if (!check_player_in_map(var, new_position_x, new_position_y))
//         return;

//     var->move->coor_x = new_position_x;

//     mlx_delete_image(var->mlx, var->img);
//     print_pixel(var);
//     print_pixel_player(var);
//     draw_line_dda(var);

// }
