/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 09:33:17 by rel-mora          #+#    #+#             */
/*   Updated: 2024/11/17 13:19:35 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	print_char_array(char **array)
{
	int	i;

	i = 0;
	if (array == NULL)
	{
		printf("Array is NULL\n");
		return ;
	}
	while (array[i] != NULL)
	{
		printf("%s\n", array[i]);
		i++;
	}
}

void	fill(t_start *var)
{
	int	i;
	int	j;

	i = 6;
	j = 0;
	while (var->content[i])
	{
		i++;
		j++;
	}
	var->map = malloc((j + 1) * sizeof(char *));
	i = 6;
	j = 0;
	while (var->content[i])
	{
		var->map[j] = ft_strdup(var->content[i]);
		i++;
		j++;
	}
	var->map[j] = NULL;
}

void	ft_check_least(char **map, char c, int *count)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == c)
				(*count)++;
			j++;
		}
		i++;
	}
}

void	validate_start_position(t_start *var, char **map)
{
	int	count;

	count = 0;
	ft_check_least(map, 'N', &count);
	ft_check_least(map, 'E', &count);
	ft_check_least(map, 'S', &count);
	ft_check_least(map, 'W', &count);
	if (count != 1)
		ft_put_error("invalide player position\n", var, NULL);
}
void	verify_input(t_start *var)
{
	int	i;
	int	j;

	j = i = 0;
	while (var->map[i] != NULL)
	{
		j = 0;
		while (var->map[i][j])
		{
			if ((var->map[i][j] != '0' && var->map[i][j] != '1')
				&& var->map[i][j] != ' ' && var->map[i][j] != '\t'
				&& (var->map[i][j] != 'N' && var->map[i][j] != 'S'
					&& var->map[i][j] != 'W' && var->map[i][j] != 'E'))
				ft_put_error("invalid character", var, NULL);
			j++;
		}
		i++;
	}
}
void	count_len_map(t_start *var)
{
	t_data_2	idx;

	idx.i = 0;
	while (var->map[idx.i])
	{
		idx.j = 0;
		while (var->map[idx.i][idx.j])
		{
			if (var->map[idx.i][idx.j] == 'E' || var->map[idx.i][idx.j] == 'N'
				|| var->map[idx.i][idx.j] == 'W'
				|| var->map[idx.i][idx.j] == 'S')
			{
				var->p_x = idx.i;
				var->p_y = idx.j;
			}
			idx.j++;
		}
		idx.i++;
	}
	var->len_x = idx.i;
	var->len_y = idx.j;
}
int	ft_check_begin(char **map, t_start *var)
{
	int	j;

	count_len_map(var);
	j = 0;
	while (map[0][j])
	{
		if (map[0][j] == '0')
			return (1);
		if ((map[0][j] == '1' || map[0][j] == '\t' || map[0][j] == ' '))
			j++;
	}
	return (0);
}
int	ft_check_wall(char **map, t_start *var)
{
	int	j;
	int	i;
	int	res;

	ft_ini_val(&i, &res);
	if (ft_check_begin(map, var))
		return (1);
	while (map[i])
	{
		res = ft_strlen(map[i]);
		if ((map[i][res - 1] != '1' && map[i][res - 1] != ' ' && map[i][res
				- 1] != '\t') || (map[i][0] != '1' && map[i][0] != ' '
				&& map[i][0] != '\t'))
			return (1);
		i++;
	}
	j = 0;
	while (map[i - 1][j])
	{
		if (map[i - 1][j] != '1' && map[i - 1][j] != ' ' && map[i
			- 1][j] != '\t')
			return (1);
		j++;
	}
	return (0);
}

char	**ft_duplicate_map(char **map, int i)
{
	char		**cpy_map;
	t_data_2	var;

	var.i = 0;
	var.j = 0;
	cpy_map = malloc((i + 1) * sizeof(char *));
	while (map[var.i])
	{
		cpy_map[var.i] = ft_strdup(map[var.i]);
		var.i++;
	}
	cpy_map[var.i] = NULL;
	return (cpy_map);
}

void	ft_flood_fill(char **cpy_map, int x, int y, t_start *var)
{
	// Check if the current position is out of bounds
	if (x < 0 || x >= var->len_x || y < 0 || y >= var->len_y)
		return ;
	// Check if the current position is NULL
	if (cpy_map[x] == NULL)
		return ;
	// Check if the current position is a space or tab
	if (cpy_map[x][y] == ' ' || cpy_map[x][y] == '\t')
	{
		free_double(var->cpy_map);
		ft_put_error("Error: Invalid map\n", var, NULL);
	}
	// Check if the current position is a player or empty space
	if (cpy_map[x][y] == 'N' || cpy_map[x][y] == 'S' || cpy_map[x][y] == 'E'
		|| cpy_map[x][y] == 'W' || cpy_map[x][y] == '0')
	{
		cpy_map[x][y] = '1';
		ft_flood_fill(cpy_map, x + 1, y, var);
		ft_flood_fill(cpy_map, x - 1, y, var);
		ft_flood_fill(cpy_map, x, y + 1, var);
		ft_flood_fill(cpy_map, x, y - 1, var);
	}
}

void	ft_check_around(t_start *var, int i, int j)
{
	if (ft_strlen(var->map[i -1]) >= (size_t)j || var->map[i-1][j] == ' ' )
	{
		free_double(var->cpy_map);
		ft_put_error("Error: invalid map\n", var, NULL);
	}
	if (var->map[i][j-1] && var->map[i][j+1] && (var->map[i][j-1] == ' ' || var->map[i][j + 1] == ' '))
	{
		free_double(var->cpy_map);
		ft_put_error("Error: invalid map\n", var, NULL);
	}
	if (ft_strlen(var->map[i + 1]) >= (size_t)j || var->map[i+1][j] == ' ' )
	{
		free_double(var->cpy_map);
		ft_put_error("Error: invalid map\n", var, NULL);
	}
}
void ft_check_empty(t_start *var)
{
	int i;
	int j;

	while(var->map[var->p_x][var->p_y] == '0')
	{
		i = 0;
		while (var->map[i])
		{
			j = 0;
			while (var->map[i][j])
			{
				if (var->map[i][j] == '0')
					ft_check_around(var, i, j);
				j++;
			}
			i++;
		}
	}
}
void	ft_check_pos(t_start *var)
{
	if (ft_strlen(var->map[var->p_x - 1]) <= (size_t)var->p_y)
	{
		free_double(var->cpy_map);
		ft_put_error("Error: invalid map\n", var, NULL);
	}
	ft_check_empty(var);
}
void	check_general(t_start *var)
{
	t_data_2	idx;

	idx.i = 0;
	idx.j = 0;
	while (var->map[idx.i])
	{
		idx.j = 0;
		while (var->map[idx.i][idx.j])
		{
			if (var->map[idx.i][idx.j] == 'E' || var->map[idx.i][idx.j] == 'N'
				|| var->map[idx.i][idx.j] == 'W'
				|| var->map[idx.i][idx.j] == 'S')
			{
				var->p_x = idx.i;
				var->p_y = idx.j;
			}
			idx.j++;
		}
		idx.i++;
	}
	var->cpy_map = NULL;
	var->cpy_map = ft_duplicate_map(var->map, idx.i);
	ft_check_pos(var);
	ft_flood_fill(var->cpy_map, var->p_x, var->p_y, var);
	free_double(var->cpy_map);
}
void	fill_map(t_start *var)
{
	fill(var);
	verify_input(var);
	validate_start_position(var, var->map);
	if (ft_check_wall(var->map, var))
	{
		ft_putstr_fd("Error: the map must surrounded by wall", 2);
		exit(1);
	}
	check_general(var);
}
