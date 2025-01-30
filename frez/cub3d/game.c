/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:37:44 by rel-mora          #+#    #+#             */
/*   Updated: 2024/11/13 16:38:09 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_to_img(t_start *var)
{
	var->config.north_g = mlx_texture_to_image(var->mlx, var->config.north_t);
	var->config.east_g = mlx_texture_to_image(var->mlx, var->config.east_t);
	var->config.south_g = mlx_texture_to_image(var->mlx, var->config.south_t);
	var->config.west_g = mlx_texture_to_image(var->mlx, var->config.west_t);
	mlx_delete_texture(var->config.east_t);
	mlx_delete_texture(var->config.north_t);
	mlx_delete_texture(var->config.south_t);
	mlx_delete_texture(var->config.west_t);
}
