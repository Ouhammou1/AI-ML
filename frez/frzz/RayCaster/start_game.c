/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:38:12 by bouhammo          #+#    #+#             */
/*   Updated: 2025/01/24 19:02:55 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"



void change_deriction(mlx_key_data_t keydata, t_start *var)
{
    if (keydata.action == MLX_RELEASE || keydata.action == MLX_REPEAT)
    {
        if (keydata.key == MLX_KEY_RIGHT)
        {
            var->draw->angle += deg_to_rad(7);
			var->draw->angle  = normalize_angle(var->draw->angle);

			mlx_delete_image(var->mlx, var->img);
			print_pixel(var);
			print_pixel_player(var);
			ft_intersection(var);
		}
        else if (keydata.key == MLX_KEY_LEFT)
        {
            var->draw->angle -= deg_to_rad(7);
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

void 	use_hook(mlx_key_data_t keydata, void* param)
{
	t_start 		*tmp_var;

	tmp_var = param;
	change_deriction(keydata, tmp_var);
	if(keydata.key == MLX_KEY_W && ( keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		move_player(keydata, tmp_var);

	if(keydata.key == MLX_KEY_S && ( keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		move_player(keydata, tmp_var);

	if(keydata.key == MLX_KEY_A && ( keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		move_player(keydata, tmp_var);

	if(keydata.key == MLX_KEY_D && ( keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		move_player(keydata, tmp_var);

	if(keydata.key == MLX_KEY_ESCAPE )
		exit(EXIT_SUCCESS);
}
void 	initialize_angle(t_start *var)
{
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
void	initialize_move_player(t_start *var )
{
	var->len_map = var->len_y * TILE_SIZE;

	var->move  = malloc(sizeof(t_move_player));
	var->draw  = malloc(sizeof(t_draw_line));
	var->ray   = malloc(sizeof(t_rays));
	var->inter = malloc(sizeof(t_position_intersec));
	var->wall  =  malloc((var->len_map + 1) * sizeof(build_walls_t));
    if (!var->move ||  !var->draw || !var->ray || !var->inter || !var->wall)
	{
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
	var->move->coor_x = var->p_y * TILE_SIZE;
	var->move->coor_y = var->p_x * TILE_SIZE;
	var->move->width_x = var->len_y * TILE_SIZE;
	var->move->height_y = var->len_x * TILE_SIZE;

initialize_angle(var);
	
}

void	ft_start_game(t_start *var)
{
	t_start 	*tmp;

	var->offset = 20;
	var->player =var->map[var->p_x][var->p_y];
	initialize_move_player(var);
	tmp = var;
	tmp->mlx = mlx_init( tmp->move->width_x, tmp->move->height_y ,"CUB3D", false);

	ft_game_is_over(tmp);
	mlx_key_hook(tmp->mlx, &use_hook, tmp);
	mlx_loop(tmp->mlx);
	mlx_terminate(tmp->mlx);
}
