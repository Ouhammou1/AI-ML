/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intersection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 21:58:25 by bouhammo          #+#    #+#             */
/*   Updated: 2024/12/07 22:49:36 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../cub.h"


void       dda(t_start *var)
{   
    if(check_is_valid(var) ==1)
        return ;
        
    var->draw->new_point_x = (var->move->coor_x / TILE_SIZE) +  (cos(var->ray->ray_angle) * TILE_SIZE);
    var->draw->new_point_y = (var->move->coor_y / TILE_SIZE) +  (sin(var->ray->ray_angle) * TILE_SIZE);


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



void drawing_line(t_start *var , int x0, int y0, int x1, int y1) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    printf(" x0 [%d]\n  y0 [%d]\n  x1 [%d]\n  y1 [%d] \n\n", x0, y0, x1, y1);


    while (true) {
        if (x0 < 0 || y0 < 0 || x0 >= var->move->width_x || y0 >= var->move->height_y)
            return;

        if (x0 == x1 && y0 == y1 )
            break;
        ft_put_pixel(var , (x0) , (y0));

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
// void    drawing_line( t_start *var, int coor_a_x, int coor_a_y, int coor_b_x, int coor_b_y)
// {

//     int dx = abs(coor_b_x - coor_a_x);
//     int dy = abs(coor_b_y - coor_a_y);
//     int sx = (coor_a_x < coor_b_x) ? 1 : -1; 
//     int sy = (coor_a_y < coor_b_y) ? 1 : -1; 
//     int err = dx - dy;

//     while (1)
//     {
 
//         if (coor_a_x < 0 || coor_a_x > var->move->width_x || coor_a_y < 0 || coor_a_y > var->move->height_y)
//         {
//             return ;
//         }
        
//         if (coor_a_x == coor_b_x || coor_a_y == coor_b_y)
//             break;
            
//             mlx_put_pixel(var->img, coor_a_x, coor_a_y, 0xFFFFFF);

//         int e2 = 2 * err;
//         if (e2 > -dy)
//         {
//             err -= dy;
//             coor_a_x += sx;
//         }
//         if (e2 < dx)
//         {
//             err += dx;
//             coor_a_y += sy;
//         }
//     }
// }


double chack_angle(double angle)
{

    // printf(" ...............   angle [%f] \n\n", angle);
    if (fabs(angle - 0.0) < EPSILON || fabs(angle - 180.0) < EPSILON || fabs(angle - 360.0) < EPSILON)
        return 1;
    return 0;
}

int check_is_wall(t_start *var, double x, double y)
{
    if (x < 0 || x >= var->move->width_x || y < 0 || y >= var->move->height_y)
        return -1;

    int map_x = (int)(x / TILE_SIZE);
    int map_y = (int)(y / TILE_SIZE);

    if (map_x < 0 || map_x >= var->move->width_x / TILE_SIZE || map_y < 0 || map_y >= var->move->height_y / TILE_SIZE)
        return -1;

    // printf(" va->map [%c] \n\n", var->map[map_y][map_x]);
    if (var->map[map_y][map_x] == '1')
        return 0;
    return 1;
}


t_position_intersec  	git_first_x_intersection( t_start *var)
{
    t_position_intersec inter;
    inter.x = 0;
    inter.y = 0;
    inter.distance = -1;
    inter.retur = -1;
    double y_inter = 0;
    double x_inter = 0;
    double x_step = 0;
    double y_step = 0;
    if(is_looking_up(var->draw->angle)== true)
    {
        y_inter =  ((floor(var->move->coor_y / TILE_SIZE)) * TILE_SIZE )  - 1;
        y_step = -TILE_SIZE;
    }
    if(is_looking_down(var->draw->angle) == true)
    {
        y_inter = ((floor(var->move->coor_y / TILE_SIZE) * TILE_SIZE)) + TILE_SIZE;
        y_step = TILE_SIZE;
    }
    
    if(cos(var->draw->angle) != 0 )//&& sin(var->draw->angle) != 0)
    {
        x_inter =  ((y_inter - var->move->coor_y) / ( (-sin(var->draw->angle)) / cos(var->draw->angle)) )  + var->move->coor_x;
        x_step = y_step / ( (-sin(var->draw->angle)) / cos(var->draw->angle));
    }

    printf(" *************************************     [-->  %f]   \n\n", rad_to_deg(var->draw->angle));
    while (check_is_wall(var , x_inter ,y_inter ) == 1)
    {
        x_inter += x_step;
        y_inter += y_step;
    }
    inter.x = x_inter;
    inter.y = y_inter;

    drawing_line(var, var->move->coor_x, var->move->coor_y, inter.x, inter.y );
    inter.distance = sqrt(pow((x_inter - var->move->coor_x), 2) + pow((y_inter - var->move->coor_y), 2));
	return inter;
}


t_position_intersec git_first_y_intersection(t_start *var)
{
    t_position_intersec inter;
    inter.x = 0;
    inter.y = 0;
    inter.distance = -1;
    inter.retur = -1;

    double x_inter = 0;
    double y_inter = 0;
    double x_step = 0;
    double y_step = 0;

    
    if(is_looking_right(var->draw->angle) == true)
    {
        printf("   ........................ OK 1  ................   \n\n");
        x_inter =   ((floor((var->move->coor_x / TILE_SIZE))) * TILE_SIZE ) + TILE_SIZE;
        x_step = TILE_SIZE;
    }
    else
    {
        printf("   ........................ OK  2 ................   \n\n");
        x_inter =   ((floor(var->move->coor_x / TILE_SIZE)) * TILE_SIZE)  - 1;
        x_step = -TILE_SIZE;
    }
    if( chack_angle(rad_to_deg(var->draw->angle)) == 1)
        return inter;

    if(cos(var->draw->angle) != 0 )
    {
    y_inter =  var->move->coor_y +  ((var->move->coor_x - x_inter ) * ((-sin(var->draw->angle)) / cos(var->draw->angle)) ) ;
    y_step = (x_step * ((-sin(var->draw->angle)) / cos(var->draw->angle)));
    }

    printf(" *************************************     [-->  %f]   \n\n", rad_to_deg(var->draw->angle));

    while (check_is_wall(var , x_inter ,y_inter ) == 1)
    {
        x_inter += x_step;
        y_inter += y_step;
    }
    inter.x = x_inter;
    inter.y = y_inter;
    drawing_line(var, var->move->coor_x, var->move->coor_y, x_inter, y_inter );
    inter.distance = sqrt(pow((x_inter - var->move->coor_x), 2) + pow((y_inter - var->move->coor_y), 2));
    return inter;
}


void	ft_intersection(t_start *var )
{
	// t_position_intersec inter_x;
	t_position_intersec inter_y;

    // inter_x = git_first_x_intersection(var);
    inter_y = git_first_y_intersection(var);





    // t_position_intersec inter_x;
	// t_position_intersec inter_y;
  
    //  inter_x = git_first_x_intersection(var);
    // inter_y = git_first_y_intersection(var);
  

            // drawing_line(var, var->move->coor_x, var->move->coor_y, inter_x.x, inter_x.y );
    // int ray=0;
	// while ( ray <= NUM_RAYS)
	// {

    // inter_x = git_first_x_intersection(var);
    // inter_y = git_first_y_intersection(var);
		
    //     if(inter_x.distance < inter_y.distance)
    //     {
    //         drawing_line(var, var->move->coor_x, var->move->coor_y, inter_x.x, inter_x.y );
    //     }
    //     else
    //     {
    //         drawing_line(var, var->move->coor_x, var->move->coor_y, inter_y.x, inter_y.y );        
    //     }
	// 	ray++;
	// }

        // new_y = git_first_y_intersection(var);
    // while (1)
    // {
    //     if( check_is_wall(var) == 1)
    //         break;
    //     // var->draw->angle += deg_to_rad( rad_to_deg(FOV_ANGLE) / NUM_RAYS);
    // }


    // if( check_is_wall(var) == 1)
    // {
        // printf(" 146466464664+-8-+8++5644694+6497+9++4+64897649764764964976 \n");
    //     new_x = git_first_x_intersection(var);
    // }
    
	// new_y = git_first_y_intersection(var);

	// int ray=0;
	// while ( ray <= NUM_RAYS)
	// {
	// 	dda(var);
	// 	var->ray->ray_angle += deg_to_rad( rad_to_deg(FOV_ANGLE) / NUM_RAYS);
	// 	ray++;
	// }
	// printf("------------->>> [%f]\n", rad_to_deg(var->ray->ray_angle));
}





















// double 	git_x_intersection( t_start *var)
// {
// 	(void)var;
// 	return 0;
// }

// void       dda(t_start *var)
// {   
//     if(check_is_valid(var) ==1)
//         return ;
        
//     var->draw->new_point_x = (var->move->coor_x / TILE_SIZE) +  (cos(var->ray->ray_angle) * TILE_SIZE);
//     var->draw->new_point_y = (var->move->coor_y / TILE_SIZE) +  (sin(var->ray->ray_angle) * TILE_SIZE);


//     double dx = var->draw->new_point_x  - (var->move->coor_x / TILE_SIZE);
//     double dy = var->draw->new_point_y  - (var->move->coor_y / TILE_SIZE);

//     double step=0;
//     if( fabs(dx) >= fabs(dy))    
//         step = fabs(dx);
//     else   
//         step = fabs(dy);
//     if( step == 0)
//         return ;        
//     double x_inc = dx / step;
//     double y_inc = dy / step;
    
//     double x = var->move->coor_x + (var->offset / 2);
//     double y = var->move->coor_y + (var->offset / 2);

//     int i=0;
//     while (i <= (step * 10)  )
//     {
//         ft_put_pixel(var , roundf(x) , roundf(y));
//         x += x_inc;
//         y += y_inc;
//         i++;
//     }
// }

// void	ft_intersection(t_start *var )
// {
// 	// int new_x;

// 	// new_x = git_x_intersection(var);
// 	int ray=0;
// 	while ( ray <= NUM_RAYS)
// 	{
// 		dda(var);
// 		var->ray->ray_angle += deg_to_rad( rad_to_deg(FOV_ANGLE) / NUM_RAYS);
// 		ray++;
// 	}
// 	printf("------------->>> [%f]\n", rad_to_deg(var->ray->ray_angle));
// }
