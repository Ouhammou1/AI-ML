/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:38:12 by bouhammo          #+#    #+#             */
/*   Updated: 2024/12/24 16:45:17 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

// int check_player_in_map(t_start *var, int new_position_x, int new_position_y)
// {
//     if (new_position_x < 0 || new_position_y < 0 ||
//         new_position_x  >= var->move->width_x ||
//         new_position_y  >= var->move->height_y ||
// 		var->map[new_position_y / TILE_SIZE][new_position_x / TILE_SIZE] == '1')
//     {
//         return 0;
//     }
// 	// if(var->map[new_position_y  + var->offset/ TILE_SIZE][new_position_x / TILE_SIZE] == '1' || 
// 	// var->map[new_position_y / TILE_SIZE][new_position_x  + var->offset/ TILE_SIZE] == '1' || 
// 	// var->map[new_position_y - var->offset/ TILE_SIZE][new_position_x / TILE_SIZE] == '1' || 
// 	// var->map[new_position_y / TILE_SIZE][new_position_x - var->offset / TILE_SIZE] == '1' )
// 	// {
// 	// 	return 0;
// 	// }
	
//     return 1;
// }



void change_deriction(mlx_key_data_t keydata, t_start *var)
{
    if (keydata.action == MLX_RELEASE || keydata.action == MLX_REPEAT)
    {
        if (keydata.key == MLX_KEY_RIGHT)
        {
            var->draw->angle += deg_to_rad(10);
			var->draw->angle  = normalize_angle(var->draw->angle);

			mlx_delete_image(var->mlx, var->img);
			print_pixel(var);
			print_pixel_player(var);
			ft_intersection(var);

		}
        else if (keydata.key == MLX_KEY_LEFT)
        {
            var->draw->angle -= deg_to_rad(10);
			var->draw->angle = normalize_angle(var->draw->angle);
	
			mlx_delete_image(var->mlx, var->img);
			print_pixel(var);
			print_pixel_player(var);
			ft_intersection(var);

        }
    }
}

void fix_rays(mlx_key_data_t keydata, t_start *var)
{
	(void)keydata;

	var->draw->angle  = normalize_angle(var->draw->angle);

	mlx_delete_image(var->mlx, var->img);
	print_pixel(var);
	print_pixel_player(var);
	ft_intersection(var);
}
void  initialize_flags(mlx_key_data_t keydata, t_start *var)
{

if(keydata.key == MLX_KEY_W)
	var->move->walk_direction = 1;
if(keydata.key == MLX_KEY_S )
	var->move->walk_direction = -1;
if(keydata.key == MLX_KEY_A )
	var->move->turn_direction = -1;
if(keydata.key == MLX_KEY_D )
	var->move->turn_direction = 1;
}
void 	use_hook(mlx_key_data_t keydata, void* param)
{
	t_start 		*tmp_var;
	tmp_var = param;

// int y = (floor(tmp_var->move->coor_y/TILE_SIZE) * TILE_SIZE)/TILE_SIZE;
// printf("-------->  cour_y [%d] \n " , y );
	// tmp_var->flag_up = false;
	// tmp_var->flag_down = false;
	change_deriction(keydata, tmp_var);

	// initialize_flags(keydata , tmp_var);
	if(keydata.key == MLX_KEY_W && ( keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		move_player(keydata, tmp_var);
		printf(" W  \n");
	}
	if(keydata.key == MLX_KEY_S && ( keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		move_player(keydata, tmp_var);
		printf(" S  \n");
	}
	if(keydata.key == MLX_KEY_A && ( keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{		
		move_player(keydata, tmp_var);
		printf(" A  \n");

	}
	if(keydata.key == MLX_KEY_D && ( keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		move_player(keydata, tmp_var);
		printf(" D \n");
	}

	if(keydata.key == MLX_KEY_ESCAPE )
	{
		exit(EXIT_SUCCESS);
	}
	
}

void	initialize_move_player(t_start *var )
{
	var->len_map = var->len_y * TILE_SIZE;

	var->move = malloc(sizeof(t_move_player));
	var->draw = malloc(sizeof(t_draw_line));
	var->ray = malloc(sizeof(t_rays));
	var->inter = malloc(sizeof(t_position_intersec));
	var->wall = (build_walls_t *)malloc((var->len_map + 1) * sizeof(build_walls_t));
    if (!var->move ||  !var->draw || !var->ray || !var->inter || !var->wall)
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
	var->move->move_speed = var->draw->angle;
}
// void	initialize_payer(t_start *var)
// {
// 		var->move->rotation_angle = deg_to_rad(270);
// 		var->move->rotation_speed = deg_to_rad(20);
// 		var->move->move_speed = 12.5;
// }
void	ft_start_game(t_start *var)
{
	t_start 	*tmp;

	var->offset = 20;
	var->player =var->map[var->p_x][var->p_y];
	initialize_move_player(var);
	// initialize_payer(var);
	tmp = var;
	tmp->mlx = mlx_init( tmp->move->width_x, tmp->move->height_y ,"CUB3D", false);

	
	ft_game_is_over(tmp);
	mlx_key_hook(tmp->mlx, &use_hook, tmp);
	mlx_loop(tmp->mlx);
	mlx_terminate(tmp->mlx);
}
