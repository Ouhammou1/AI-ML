/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 17:34:00 by bouhammo          #+#    #+#             */
/*   Updated: 2024/12/24 21:31:14 by bouhammo         ###   ########.fr       */
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

void    draw_floor_ceiling(t_start *var)
{
    int i = 0;
    while (i < var->move->height_y /2)
    {
        int j = 0;
        while (j < var->move->width_x)
        {
            ft_put_pixel_color(var, j, i ,0x556B2FFF );
            j++;
        }
        i++;
    }
    i = var->move->height_y /2;
    while (i < var->move->height_y)
    {
        int j = 0;
        while (j < var->move->width_x)
        {
            ft_put_pixel_color(var, j, i , 0x808080FF );
            j++;
        }
        i++;
    }
    return ;
}

int     get_bottom_p( t_start *var , int line)
{
    int get_b_pxl ;
    get_b_pxl = (var->move->height_y / 2) + (line / 2);

    if(get_b_pxl > var->move->height_y)
        get_b_pxl = var->move->height_y;
        
    return get_b_pxl;
}
int     get_top_p( t_start *var , int line)
{
    int get_tp_pxl ;

    get_tp_pxl = (var->move->height_y / 2) - (line / 2);
    if(get_tp_pxl > var->move->height_y)
        get_tp_pxl = var->move->height_y;
    return get_tp_pxl ;
}


void          build_walls(t_start *var , int ray) 
{
    double distance;
    double dis_projection_plan;
    double line;
    double get_top;
    double get_bottom;
    double top_pxl;

    distance = var->wall[ray].distance * cos(var->ray->ray_angle - var->draw->angle);
    dis_projection_plan = ((var->move->width_x / 2) * (tan(deg_to_rad(rad_to_deg(FOV_ANGLE) / 2))));
    line = (TILE_SIZE / distance) * dis_projection_plan;
    get_top = (int)line ;
    
    get_bottom =  get_bottom_p(var, get_top);
    top_pxl = get_top_p(var, get_top);



    while (top_pxl < get_bottom)
    {
        ft_put_pixel_color(var, ray, top_pxl ,0x4B0082FF ) ;//0x00FF00FF );
        top_pxl++;
    }
}


void        check_distance(t_start *var,double  len_a,double len_b , int ray)
{
    if (len_a == INT_MIN )
        len_a = 9999;
    if( len_b == INT_MIN)
        len_b = 9999;

    if (len_a < len_b)
    {
        // drawing_line(var, var->move->coor_x, var->move->coor_y, var->ray->x_inter_horizontal , var->ray->y_inter_horizontal);
        var->wall[ray].pos_x = var->ray->x_inter_horizontal;
        var->wall[ray].pos_y = var->ray->y_inter_horizontal;
        var->wall[ray].distance = len_a;
    }
    else
    {
        // drawing_line(var, var->move->coor_x, var->move->coor_y, var->ray->x_inter_vertical , var->ray->y_inter_vaertical);
        var->wall[ray].pos_x = var->ray->x_inter_vertical;
        var->wall[ray].pos_y = var->ray->y_inter_vaertical;
        var->wall[ray].distance = len_b;
    }
}

void ft_intersection(t_start *var)
{
    int ray;
    double len_a;
    double len_b;

    draw_floor_ceiling(var);
    var->ray->ray_angle = var->draw->angle  -  deg_to_rad(rad_to_deg(FOV_ANGLE) / 2);
    var->ray->ray_angle = normalize_angle(var->ray->ray_angle);
    ray =0;
    while (ray <= var->len_map)
    {
        git_first_x_intersection(var);
        git_first_y_intersection(var);
        len_a = sqrt(pow(var->ray->x_inter_horizontal - var->move->coor_x , 2) + pow(var->ray->y_inter_horizontal - var->move->coor_y , 2));
        len_b = sqrt(pow(var->ray->x_inter_vertical - var->move->coor_x , 2) + pow(var->ray->y_inter_vaertical - var->move->coor_y , 2));
        check_distance(var, len_a, len_b, ray);
        build_walls(var , ray);
        var->ray->ray_angle += deg_to_rad(rad_to_deg(FOV_ANGLE) / var->len_map);
        var->ray->ray_angle = normalize_angle(var->ray->ray_angle);
        ray++;
    }
}

