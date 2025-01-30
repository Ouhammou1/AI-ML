/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 17:34:00 by bouhammo          #+#    #+#             */
/*   Updated: 2025/01/24 18:55:57 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void    print_walls(t_start *var)
{
    int i = 0;
    while (i < var->len_map)
    {
        printf("wall[%d]  x [%f]  y [%f]  distance [%f] \n", i, var->wall[i].pos_x, var->wall[i].pos_y, var->wall[i].distance);
        i++;
    }

}
void draw_floor_ceiling(t_start *var) {
    double i = 0;
    while (i < var->move->height_y / 2) {
        double j = 0;
        while (j < var->move->width_x) {
            ft_put_pixel_color(var, j, i, 0x8B4513FF); // Use ceiling color from parsing
            j++;
        }
        i++;
    }
    i = var->move->height_y / 2;
    while (i < var->move->height_y) {
        double j = 0;
        while (j < var->move->width_x) {
            ft_put_pixel_color(var, j, i,0x808080FF); // Use floor color from parsing
            j++;
        }
        i++;
    }
}

int get_bottom_p(t_start *var, int line) {
    int get_b_pxl = (var->move->height_y / 2) + (line / 2);
    if (get_b_pxl > var->move->height_y)
        get_b_pxl = var->move->height_y;
    return get_b_pxl;
}

int get_top_p(t_start *var, int line) {
    int get_tp_pxl = (var->move->height_y / 2) - (line / 2);
    if (get_tp_pxl < 0) // Corrected: Check for going below 0
        get_tp_pxl = 0;
    return get_tp_pxl;
}

void build_walls(t_start *var, int ray) {
    double distance;
    double dis_projection_plan;
    double line;
    int top_pxl;
    int bottom_pxl; // Renamed for clarity
    int y = 0; // Added for clarity
    distance = (var->wall[ray].distance) * cos(var->wall[ray].angle - var->draw->angle);
    dis_projection_plan = ((var->move->width_x / 2) / (tan(deg_to_rad(rad_to_deg(FOV_ANGLE) / 2)))); // Corrected: Division instead of multiplication
    line = (TILE_SIZE / distance) * dis_projection_plan;

    top_pxl = (int) line; //get_top_p(var, line); // Use line directly
    bottom_pxl = get_bottom_p(var, top_pxl); // Use line directly
    y = get_top_p(var, bottom_pxl); // Added for clarity
    while (y < bottom_pxl)
    {
        if(var->wall[ray].c == 'h')
            ft_put_pixel_color(var, ray, y++, 0x00FF00FF); // Use wall color from parsing
        else
            ft_put_pixel_color(var, ray, y++ , 0x0000FFFF); // Use wall color from parsing
        // y++;
    }
}
// void    draw_floor_ceiling(t_start *var)
// {
//     int i = 0;
//     while (i < var->move->height_y /2)
//     {
//         int j = 0;
//         while (j < var->move->width_x)
//         {
//             ft_put_pixel_color(var, j, i ,0x8B4513FF );
//             j++;
//         }
//         i++;
//     }
//     i = var->move->height_y /2;
//     while (i < var->move->height_y)
//     {
//         int j = 0;
//         while (j < var->move->width_x)
//         {
//             ft_put_pixel_color(var, j, i , 0x808080FF );
//             j++;
//         }
//         i++;
//     }
//     return ;
// }

// double     get_bottom_p( t_start *var , double line)
// {
//     double get_b_pxl ;
//     get_b_pxl = (var->move->height_y / 2) + (line / 2);

//     if(get_b_pxl > var->move->height_y)
//         get_b_pxl = var->move->height_y;
        
//     return get_b_pxl;
// }
// double     get_top_p( t_start *var , double line)
// {
//     double get_tp_pxl ;

//     get_tp_pxl = (var->move->height_y / 2) - (line / 2);
//     if(get_tp_pxl > var->move->height_y)
//         get_tp_pxl = var->move->height_y;
//     return get_tp_pxl ;
// }


// void    build_walls(t_start *var , int ray) 
// {
//     double distance;
//     double dis_projection_plan;
//     double line;
//     double get_top;
//     double get_bottom;
//     double top_pxl;

//     distance = (var->wall[ray].distance ) * cos(var->wall[ray].angle - var->draw->angle);
//     dis_projection_plan = ((var->move->width_x / 2) * (tan(deg_to_rad(rad_to_deg(FOV_ANGLE) / 2))));
//     line = (TILE_SIZE / distance) * dis_projection_plan;
//     get_top = line ;
//     get_bottom =  get_bottom_p(var, get_top) ;
//     top_pxl = get_top_p(var, get_top);
//     while (top_pxl < get_bottom)
//     {
//         ft_put_pixel_color(var, ray, top_pxl ,0x00BFFFFF ) ;//0x00FF00FF );
//         top_pxl++;
//     }
// }


void        check_distance(t_start *var,double  len_a,double len_b , int ray)
{
    // if (len_a == INT_MIN )
    //     len_a = 9999;
    // if( len_b == INT_MIN)
    //     len_b = 9999;

    if (len_a < len_b)
    {
        drawing_line(var, var->move->coor_x, var->move->coor_y, var->ray->x_inter_horizontal , var->ray->y_inter_horizontal);
        var->wall[ray].pos_x = var->ray->x_inter_horizontal;
        var->wall[ray].pos_y = var->ray->y_inter_horizontal;
        var->wall[ray].distance = len_a ;
        var->wall[ray].angle = var->ray->ray_angle;
        var->wall[ray].c = 'h';
    }
    else
    {
        drawing_line(var, var->move->coor_x, var->move->coor_y, var->ray->x_inter_vertical , var->ray->y_inter_vaertical);
        var->wall[ray].pos_x = var->ray->x_inter_vertical;
        var->wall[ray].pos_y = var->ray->y_inter_vaertical;
        var->wall[ray].distance = len_b ;
        var->wall[ray].angle = var->ray->ray_angle;
        var->wall[ray].c = 'v';
    }
}

double ft_power(double x, double y)
{
    double res = (x - y) * (x - y);
    
    return res;
}
void ft_intersection(t_start *var)
{
    double ray;
    double len_a;
    double len_b;

    // draw_floor_ceiling(var);
    var->ray->ray_angle = var->draw->angle  -  deg_to_rad(rad_to_deg(FOV_ANGLE) / 2);
    var->ray->ray_angle = normalize_angle(var->ray->ray_angle);
    ray =0;
    while (ray < var->len_map )
    {
        git_first_x_intersection(var);
        git_first_y_intersection(var);
        var->ray->ray_angle = normalize_angle(var->ray->ray_angle);
        
        len_a = sqrt(ft_power(var->ray->x_inter_horizontal - var->move->coor_x , 2) + ft_power(var->ray->y_inter_horizontal - var->move->coor_y , 2));
        len_b = sqrt(ft_power(var->ray->x_inter_vertical - var->move->coor_x , 2) + ft_power(var->ray->y_inter_vaertical - var->move->coor_y , 2));
        // len_a = sqrt(pow(var->ray->x_inter_horizontal - var->move->coor_x , 2) + pow(var->ray->y_inter_horizontal - var->move->coor_y , 2));
        // len_b = sqrt(pow(var->ray->x_inter_vertical - var->move->coor_x , 2) + pow(var->ray->y_inter_vaertical - var->move->coor_y , 2));
        check_distance(var, len_a, len_b, ray);
        var->ray->ray_angle += deg_to_rad(rad_to_deg(FOV_ANGLE) / var->len_map);
        // build_walls(var , ray);
        ray++;
    }
}














// int get_top_pixel(t_game game, int wall_strip_hight)
// {
//   int wall_top_pixel;

//   wall_top_pixel = (game->height / 2) - (wall_strip_hight / 2);
//   if(wall_top_pixel < 0)
//     wall_top_pixel = 0;
//   return wall_top_pixel;
// }

// int get_bottom_pixel(t_gamegame, int wall_strip_hight)
// {
//   int wall_bottom_pixel;
//   wall_bottom_pixel = (game->height / 2) + (wall_strip_hight / 2);
//   if(wall_bottom_pixel > game->height)
//     wall_bottom_pixel = game->height;
//   return wall_bottom_pixel;
// }





// void render_walls(t_game game, t_rayrays)
// {
//   int i;
//   double distance_proj_plane;
//   double proj_wall_height;
//   double perp_distance;
//   int wall_strip_hight;
//   int wall_bottom_pixel;
//   int y;

//   i = 0;
//   while(i < NUM_RAYS)
//   {
//     perp_distance = rays[i].distance * cos(rays[i].ray_angle - game->player.rotation_angle);
//     distance_proj_plane = (game->width / 2) * tan(FOV / 2);
//     proj_wall_height = (TILE_SIZE / perp_distance) * distance_proj_plane;

    
//     wall_strip_hight = (int)proj_wall_height;
//     wall_bottom_pixel = get_bottom_pixel(game, wall_strip_hight);
//     y = get_top_pixel(game, wall_strip_hight);
//     while(y < wall_bottom_pixel) 
//       ft_put_pixel(game->img, i, y++, BEIGE);
//     i++;
//   }
// }