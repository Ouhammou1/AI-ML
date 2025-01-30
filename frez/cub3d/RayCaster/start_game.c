/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:38:12 by bouhammo          #+#    #+#             */
/*   Updated: 2024/12/01 13:44:24 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int check_player_in_map(t_start *var, int new_position_x, int new_position_y)
{
    if (new_position_x < 0 || new_position_y < 0 ||
        new_position_x  >= var->move->width_x ||
        new_position_y  >= var->move->height_y ||
        var->map[new_position_y / TILE_SIZE][new_position_x / TILE_SIZE] == '1')
    {
        return 0;
    }
    return 1;
}

void move_player(t_start *var, int dx, int dy)
{
    int new_position_x = var->move->coor_x + dx;
    int new_position_y = var->move->coor_y + dy;

    if (!check_player_in_map(var, new_position_x, new_position_y))
        return;

    var->move->coor_x = new_position_x;
    var->move->coor_y = new_position_y;

    mlx_delete_image(var->mlx, var->img);
    print_pixel(var);
    print_pixel_player(var );
}


// void change_deriction(mlx_key_data_t keydata, t_start *var)
// {
//     if (keydata.action == MLX_RELEASE || keydata.action == MLX_REPEAT)
//     {
//         if (keydata.key == MLX_KEY_RIGHT)
//         {
// 			mlx_delete_image(var->mlx, var->img);
// 			print_pixel(var);
// 			print_pixel_player(var);
// 			ft_intersection(var);
			
//             var->draw->angle = deg_to_rad(fmod(rad_to_deg(var->draw->angle) + 5, 360));
// 			var->ray->ray_angle = deg_to_rad(fmod(rad_to_deg(var->draw->angle) - (rad_to_deg(FOV_ANGLE) / 2) + 360, 360));
// 		}
//         else if (keydata.key == MLX_KEY_LEFT)
//         {
// 			mlx_delete_image(var->mlx, var->img);
// 			print_pixel(var);
// 			print_pixel_player(var);
// 			ft_intersection(var);

//             var->draw->angle = deg_to_rad(fmod(rad_to_deg(var->draw->angle) - 5 + 360, 360));
// 			var->ray->ray_angle = deg_to_rad(fmod(rad_to_deg(var->draw->angle) - (rad_to_deg(FOV_ANGLE) / 2) + 360, 360));
        
//         }
//     }
// }

void change_deriction(mlx_key_data_t keydata, t_start *var)
{
    if (keydata.action == MLX_RELEASE || keydata.action == MLX_REPEAT)
    {
        if (keydata.key == MLX_KEY_RIGHT)
        {
			int y = 1;
            var->draw->angle += deg_to_rad(  5 ) * y;
			if(rad_to_deg(var->draw->angle ) > 360)
			{
				var->draw->angle = deg_to_rad(rad_to_deg(var->draw->angle) - 360);
			}

			mlx_delete_image(var->mlx, var->img);
			print_pixel(var);
			print_pixel_player(var);
			ft_intersection(var);
			
			// var->draw->angle = deg_to_rad(fmod(rad_to_deg(var->draw->angle) + 360, 360));
			// if(rad_to_deg(var->draw->angle ) >= 360)
			// {
			// 	var->draw->angle = deg_to_rad(rad_to_deg(var->draw->angle) - 360);
			// }
			
			// var->ray->ray_angle = deg_to_rad(fmod(rad_to_deg(var->draw->angle) - (rad_to_deg(FOV_ANGLE) / 2) + 360, 360));
		}
        else if (keydata.key == MLX_KEY_LEFT)
        {
			int y = -1;
            var->draw->angle += deg_to_rad(  5 ) * y;
			if (rad_to_deg(var->draw->angle) < 0)
			{
				var->draw->angle = deg_to_rad(rad_to_deg(var->draw->angle) + 360);
			}

			
			mlx_delete_image(var->mlx, var->img);
			print_pixel(var);
			print_pixel_player(var);
			ft_intersection(var);

			
			// var->draw->angle = deg_to_rad(fmod(rad_to_deg(var->draw->angle) + 360, 360));

            // var->draw->angle = deg_to_rad(rad_to_deg(var->draw->angle) - 5);
			// if(rad_to_deg(var->draw->angle ) < 0)
			// {
			// 	var->draw->angle = deg_to_rad(rad_to_deg(var->draw->angle) + 360);
			// }
            // var->draw->angle = deg_to_rad(fmod(rad_to_deg(var->draw->angle) - 5 + 360, 360));
			// var->ray->ray_angle = deg_to_rad(fmod(rad_to_deg(var->draw->angle) - (rad_to_deg(FOV_ANGLE) / 2) + 360, 360));
        
        }
    }
}

void 	use_hook(mlx_key_data_t keydata, void* param)
{
	t_start 		*tmp_var;
	tmp_var = param;

// int y = (floor(tmp_var->move->coor_y/TILE_SIZE) * TILE_SIZE)/TILE_SIZE;
// printf("-------->  cour_y [%d] \n " , y );
	tmp_var->flag_up = false;
	tmp_var->flag_down = false;
	change_deriction(keydata, tmp_var);

	if(keydata.key == MLX_KEY_W && ( keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		tmp_var->flag_up = true;
		move_player_up(tmp_var , 0, -tmp_var->offset );
		printf(" W  \n");
	}
	if(keydata.key == MLX_KEY_S && ( keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		tmp_var->flag_down = true;
		move_player_down(tmp_var , 0 , tmp_var->offset);
		printf(" S  \n");
	}
	if(keydata.key == MLX_KEY_A && ( keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{		
		move_player_left(tmp_var , - tmp_var->offset , 0);
		printf(" A  \n");

	}
	if(keydata.key == MLX_KEY_D && ( keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		move_player_right(tmp_var ,tmp_var->offset, 0  );
		printf(" D \n");
	}
	if(keydata.key == MLX_KEY_ESCAPE )
	{
		exit(EXIT_SUCCESS);
	}
	
}

void	initialize_move_player(t_start *var )
{
	var->move = malloc(sizeof(t_move_player));
	var->draw = malloc(sizeof(t_draw_line));
	var->ray = malloc(sizeof(t_rays));
	var->ray = malloc(sizeof(t_position_intersec));
    if (!var->move ||  !var->draw || !var->ray)
	{
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
	var->move->coor_x = var->p_y * TILE_SIZE;
	var->move->coor_y = var->p_x * TILE_SIZE;
	var->move->width_x = var->len_y * TILE_SIZE;
	var->move->height_y = var->len_x * TILE_SIZE;
	double angle=0;
	if(var->player == 'N')
	{
		angle = 270;
		var->ray->ray_angle = deg_to_rad(angle - (rad_to_deg(FOV_ANGLE) / 2));
	}
	if(var->player == 'E')
	{
		angle = 90;
		var->ray->ray_angle = deg_to_rad(angle - (rad_to_deg(FOV_ANGLE) / 2));
	}
	if(var->player == 'S')
	{
		angle = 0;
		var->ray->ray_angle = deg_to_rad(angle - (rad_to_deg(FOV_ANGLE) / 2));
	}
	if(var->player == 'W')
	{
		angle = 180;
		var->ray->ray_angle = deg_to_rad(angle - (rad_to_deg(FOV_ANGLE) / 2));
	}
	var->draw->angle = deg_to_rad(angle);
}
void	initialize_flags(t_start *var)
{
	var->move->flag_up = 0;
	var->move->flag_down = 0;
	var->move->flag_right = 0;
	var->move->flag_left = 0;
}
void	ft_start_game(t_start *var)
{
	t_start 	*tmp;

	var->offset = 20;
	var->player =var->map[var->p_x][var->p_y];
	initialize_move_player(var);
	initialize_flags(var);
	tmp = var;
	tmp->mlx = mlx_init( tmp->move->width_x, tmp->move->height_y ,"CUB3D", false);
	




	ft_game_is_over(tmp);
	mlx_key_hook(tmp->mlx, &use_hook, tmp);
	mlx_loop(tmp->mlx);
	mlx_terminate(tmp->mlx);
}
