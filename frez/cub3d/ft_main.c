/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 16:43:06 by rel-mora          #+#    #+#             */
/*   Updated: 2024/11/08 19:48:37 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_initialize(t_start *var)
{
	var->content = NULL;
}

void	ff(void)
{
	system("leaks cub3d");
}
int	main(int ac, char **av)
{
	t_start	var;

	if (ac == 2)
	{
		ft_initialize(&var);
		ft_validate(av[1], &var);
		ft_start_game(&var);
	}
	else
		ft_put_error("Error: The argument is not valid\n", NULL, NULL);
	free_start(&var);
}
