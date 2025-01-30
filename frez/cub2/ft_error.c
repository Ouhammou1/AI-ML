/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <reduno96@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 15:16:28 by rel-mora          #+#    #+#             */
/*   Updated: 2024/11/04 08:52:57 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_put_error(char *s, t_start *var, t_data *to)
{
	ft_putstr_fd(s, 2);
	free_start(var);
	if (to)
		free_trim(to);
	exit(1);
}

void	ft_just_print_error(char *s)
{
	ft_putstr_fd(s, 2);
	while (1)
		;
}
