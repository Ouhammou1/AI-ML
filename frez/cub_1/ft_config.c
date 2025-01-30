/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_config.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:33:35 by rel-mora          #+#    #+#             */
/*   Updated: 2024/11/08 19:48:07 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_to_space(char *trim)
{
	int	i;

	i = 0;
	while (trim[i])
	{
		if (trim[i] == '\t' || trim[i] == ' ')
			return (i);
		i++;
	}
	return (i);
}

void	ft_ini_var_to(t_var *idx, t_data *to)
{
	idx->count = 0;
	idx->j = 0;
	to->sub = NULL;
	to->set = NULL;
	to->trim = NULL;
	idx->i = 0;
}

int	ft_config_img(t_start *var, char *sub, char *set)
{
	char	*clean;

	clean = ft_strtrim(set, " \t");
	if (ft_search(sub, "NO"))
		var->config.north_t = mlx_load_png((clean));
	else if (ft_search(sub, "SO"))
		var->config.south_t = mlx_load_png((clean));
	else if (ft_search(sub, "EA"))
		var->config.east_t = mlx_load_png((clean));
	else if (ft_search(sub, "WE"))
		var->config.west_t = mlx_load_png((clean));
	else
		return (free(clean), 1);
	free(clean);
	return (0);
}

int	ft_set_element(t_start *var)
{
	t_var	idx;
	t_data	to;

	ft_ini_var_to(&idx, &to);
	while (var->config.element[idx.i] != NULL)
	{
		to.trim = ft_strtrim(var->config.element[idx.i], " \t");
		idx.j = ft_to_space(to.trim);
		to.sub = ft_substr(to.trim, 0, idx.j);
		to.set = ft_substr(to.trim, idx.j + 1, ft_strlen(to.trim));
		if (idx.j == 1)
			ft_config_rgb(var, &to, &idx.count);
		else if (idx.j == 2)
			ft_config_img(var, to.sub, to.set);
		else
			return (free_trim(&to), 1);
		idx.i++;
		free_trim(&to);
	}
	if (!var->config.west_t || !var->config.east_t || !var->config.south_t
		|| !var->config.north_t || idx.count != 2)
		return (free_trim(&to), 1);
	return (0);
}

void	fill_config(t_start *var)
{
	int	i;

	var->config.element = malloc(7 * sizeof(char *));
	i = 0;
	while (var->content[i] && i < 6)
	{
		var->config.element[i] = ft_strdup(var->content[i]);
		i++;
	}
	var->config.element[i] = NULL;
	if (ft_set_element(var))
		ft_put_error("Error: in configuration of the map.", var, NULL);
}
