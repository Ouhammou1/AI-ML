/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:40:33 by bouhammo          #+#    #+#             */
/*   Updated: 2024/12/24 20:19:41 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void		ft_error()
{
	printf("Error :\n");
	exit(EXIT_FAILURE);
}

int 	ft_caracter(char  Y)
{
	if( Y == 'N' ||  Y == 'S' || Y == 'W'  || Y == 'E' )
		return 1;
	return 0;
}

void	print_in_wall(t_start *var , int x_map,int y_map)
{
	int k = y_map;
	while (k < y_map + TILE_SIZE )
	{
		int len = x_map;
		while (len < x_map + TILE_SIZE  )
		{
			mlx_put_pixel(var->img, len , k, 0x000004FF );
			len++;
		}
		k++;
	}
}

void	print_in_space(t_start *var, int   x_map, int  y_map)
{
	int k = y_map;
	while (k < y_map + TILE_SIZE )
	{
		int len = x_map ;
		while (len < x_map + TILE_SIZE  )
		{
			mlx_put_pixel(var->img, len , k,  0x6A5AF);
			len++;
		}
		k++;
	}
}

void	print_pixel( t_start  *var)
{
	t_start *tmp;
	int i;
	int y_map;
	int j;
	int x_map;

	tmp = var;
	if (!tmp || !tmp->map)
		ft_error();
	tmp->img = mlx_new_image(tmp->mlx,tmp->move->width_x  , tmp->move->height_y );
	if(!tmp->img || (mlx_image_to_window(tmp->mlx, tmp->img ,0 ,0) < 0))
		ft_error();
	i=0;
	y_map =0;
	while (tmp->map[i])
	{
		x_map =0; 
		j = 0;
		while (tmp->map[i][j])
		{
			if(tmp->map[i][j] == '1' )
				print_in_wall(tmp,  x_map, y_map);
			if(tmp->map[i][j] == '0' || ft_caracter(tmp->map[i][j]) == 1)
				print_in_space(tmp,  x_map, y_map);
			x_map +=TILE_SIZE;
			j++;
		}
		y_map +=TILE_SIZE;
		i++;
	}
}

void print_pixel_player(t_start *var)
{
    if (!var || !var->img || !var->map)
        return;

    int x_map = var->move->coor_x;
    int y_map = var->move->coor_y;

	int y = y_map;
	while (y  < y_map + var->offset)
	{
		int x = x_map;
		while (x < x_map + var->offset - 2)
		{
			mlx_put_pixel(var->img, x, y , 0xFFFF00FF); 
			x++;
		}
		y++;
	}
}

void	ft_game_is_over(t_start *var)
{

	if (!var || !var->content)
		ft_error();
	print_pixel(var);
	print_pixel_player(var );
	ft_intersection(var);
}
