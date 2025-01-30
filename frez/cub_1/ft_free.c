/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 18:47:12 by rel-mora          #+#    #+#             */
/*   Updated: 2024/11/08 19:48:31 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	free_double(char **array)
{
	int	i;

	i = 0;
	if (array == NULL)
	{
		return ;
	}
	while (array[i] != NULL)
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}

void	free_trim(t_data *to)
{
	if (to)
	{
		if (to->trim)
		{
			free(to->trim);
			to->trim = NULL;
		}
		if (to->sub)
		{
			free(to->sub);
			to->sub = NULL;
		}
		if (to->set)
		{
			free(to->set);
			to->set = NULL;
		}
		to = NULL;
	}
}

void	free_start(t_start *var)
{
	if (var)
	{
		free_double(var->content);
		free_double(var->config.element);
		if (!var->map)
			free_double(var->map);
		var = NULL;
	}
}
