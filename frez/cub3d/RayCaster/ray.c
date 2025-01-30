/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:40:33 by bouhammo          #+#    #+#             */
/*   Updated: 2024/11/24 22:52:22 by bouhammo         ###   ########.fr       */
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
void	print_pixel( t_start  *var)
{
	t_start *tmp;
	tmp = var;
	if (!tmp || !tmp->map)
		ft_error();

	var->img = mlx_new_image(tmp->mlx,tmp->move->width_x  , tmp->move->height_y );
	if(!var->img || (mlx_image_to_window(tmp->mlx, tmp->img ,0 ,0) < 0))
		ft_error();

	int i=0;
	int y_map =0;

	while (var->map[i])
	{
		int j =0;
		int x_map =0; 

		while (var->map[i][j])
		{
			if(var->map[i][j] == '1' )
			{
				int k = y_map;
				while (k < y_map + TILE_SIZE -1)
				{
					int len = x_map;
					while (len < x_map + TILE_SIZE - 1 )
					{
						mlx_put_pixel(tmp->img, len , k, 0x000004FF );
						len++;
					}
					k++;
				}
			}
			if(var->map[i][j] == '0' || ft_caracter(var->map[i][j]) == 1)
			{
				int k = y_map;
				while (k < y_map + TILE_SIZE -1)
				{
					int len = x_map ;
					while (len < x_map + TILE_SIZE - 1 )
					{
						mlx_put_pixel(tmp->img, len , k,  0x6A5AF);
						len++;
					}
					k++;
				}
			}
			x_map +=TILE_SIZE;
			j++;
		}
		y_map +=TILE_SIZE;
		i++;
	}
}
char 	 **list_map(t_start *var )
{
	t_start *tmp;
	tmp = var;

	int i =0;
	char **list;

	while (tmp->map[i])
		i++;
	list = (char **)malloc((i + 1) * sizeof(char*));
	if(list == NULL)
		return NULL;

	i =0;
	while (tmp->map[i])
	{
		list[i] = ft_strdup(tmp->map[i]);
		i++;
	}
	list[i] = NULL;
	return list;
}
int get_r(int rgba)
{
    return ((rgba >> 24) & 0xFF);
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
    draw_line_dda(var);
}
